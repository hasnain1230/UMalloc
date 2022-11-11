#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "umalloc.h"

/*
 * These represent the ASCII values of 'T' and 'F' respectively. These are used to represent true and false respectively.
 */

#define TRUE 84
#define FALSE 70

static char memory[MEMSIZE]; // Assuming that everything in the char array is 0.

/*
 * For metaData, available is set to type char to represent boolean values of true or false. These will ALWAYS be either
 * set to upper case ASCII 'T' (84 decimal value) or upper case ASCII 'F' (70 decimal value). These values will represent
 * true and false respectively. The reason char is used because the memory array by default has all the values set to 0.
 * If we were to use `stdbool`, if we set "available" to false, it would be very half to know if the zero read in the array
 * is "false" or if the zero means that this part of the array has not been read yet. It is just to prevent confusion.
 * `stdbool` values are one byte by default on x86 and x86_64 architecture. So are chars. It is safe to assume "available" will
 * not be set to anything else.
 *
 * Furthermore, the use of "char" here is also risky and may be confusing because chars are typically associated with "characters",
 * however, in this case, to use the simplest and easiest to understand solution, the `available` variable in metaData is to be
 * viewed only as a boolean value represented by the 'T' and 'F' ASCII characters. This is only done to prevent confusion with the
 * default char value in the memory array.
 */

struct metaData {
    char available; // In this case, available will either be set as T or F for true or false.
    unsigned int dataSize; // We did not use size_t here to save space in the long run. Rather than having a 16 byte alignment, doing unsigned int makes it 8 byte aligned which will save space. I think it is safe to assume that the user will not be allocating more than 4 GB of memory all at once should the memory be 2^32 bytes large.
};

void printMemory(int bytes) { // This function was created for debugging purposes. The user may call this if they may to view "bytes" number of bytes in the memory array. This function is only intended to be used for debugging purposes.
    if (bytes > MEMSIZE) {
        printf("You cannot print more than %d bytes from the memory array!\n\n", MEMSIZE);
        return;
    }
    for (int x = 0; x < bytes; x++) {
        printf("Address %d: %p\n", x, memory + x);
        printf("Value: %x\n", memory[x]);
    }
}

/*
 * The function below initializeMemory() initializes memory on the first call to malloc. It is only over called once or if
 * for some reason, the memoryArray gets entirely wiped out at runtime (due to user error) and the memory is set to zero.
 * This function creates two pieces of metaData. First, it allocates the memory that was requested, then it makes a second metaData to the right
 * of it storing how much is actually left for the user to allocate (after all the metaData insert calculations). See README for more details on this
 * design strategy.
 */

void *initializeMemory(size_t size) {
    struct metaData *md = (struct metaData *) memory; // md's actual contents gets written to the same place where memory is stored. It starts writing at the address of memory[0]

    md->available = FALSE;
    md->dataSize = size;

    md = (struct metaData *) &memory[sizeof(struct metaData) + md->dataSize]; // Have md point to basically after the metadata and allocated memory given to the user.

    md->available = TRUE;
    md->dataSize = MEMSIZE - (sizeof(struct metaData) * 3) - size; // How much memory there is left to allocate. Here, we are accounting for three metaData structs. The one made by user, the one storing how much data is left over, and space for the next metaData that will be stored on the next malloc call.

    return memory + sizeof(struct metaData); // Return pointer to first allocated memory.
}

/*
 * This function is called at the end of every free call. It looks through the array, looking for two adjacent free blocks next to each other.
 * If there are two adjacent free blocks next to each other, this function will combine their metaData (and the data allocated with each piece of dataData)
 * essentially combining them together. Please see README for more details.
 */

void coalesceBlocks() {
    int x = 0;
    while (x < MEMSIZE) {
        struct metaData *firstMetaData = (struct metaData *) &memory[x];

        int nextMDLocation = x + sizeof(struct metaData) + firstMetaData->dataSize; // The location of the next metaData in the array.

        if (nextMDLocation + sizeof(struct metaData) > MEMSIZE) { // If we are at the last piece of metaData and there is nothing else to the right. Nothing to allocate.
            return;
        }

        struct metaData *secondMetaData = (struct metaData *) &memory[nextMDLocation];

        if (firstMetaData->available == TRUE && secondMetaData->available == TRUE) {
            firstMetaData->dataSize += (secondMetaData->dataSize + sizeof(struct metaData)); // Combine the two blocks, the data they have allocated, and one of their metaDatas.
            continue;
        }

        x += sizeof(struct metaData) + firstMetaData->dataSize; // Iterate through array based on metaData.
    }
}

/*
 * My malloc (will be called by a call to malloc, see mymalloc.h). This function will allocate a chunk of memory from the memory array
 * that is statically and globally defined (essentially, it cannot be accessed outside this file). This function will create some metaData,
 * store it in the array, (indicating that the next specified chunk is occupied), then return the allocated chunk to the user. This function will also (if there is no metaData),
 * create a new piece of metaData to the right which will calculate how much space the user has left to allocate (including if they were to call malloc again), and store in the second metaData (that is stored to the right)
 * how CALLABLE memory the user has left. Please see README for more details.
 */

void *umalloc(size_t size, char *file, int line) {
    if (size + (2 * sizeof(struct metaData)) > MEMSIZE) { // If the user physically calls too much memory.
        tooMuchMem(MEMSIZE, file, line);
        return NULL;
    }

    if (size <= 0) {
        mallocZeroError(file, line); // The user is not allowed to call zero or fewer bytes. Doing so causes issues; real malloc allows for this, but we do not.
        return NULL;
    }

    if (memory[0] == 0) { // Initialize the memory.
        return initializeMemory(size); // This function was made because I wanted to keep initializeMemory code separate from everything else.
    }


    int x = 0;

    while (x < MEMSIZE) { // Iterate through memory to look for a block big enough for size.
        struct metaData *md = (struct metaData *) &memory[x];

        if (md->available == TRUE && md->dataSize >= size) { // Found a block big enough.

            md->available = FALSE;
            md->dataSize = size;

            unsigned int nextMDIndex = x + sizeof(struct metaData) + md->dataSize;

            md = (struct metaData *) &memory[nextMDIndex]; // The next metaData that is or may need to be stored to the right of this currently allocated chunk.

            if (md->available != TRUE && md->available != FALSE) { // This means that there is no metaData to the right, and we need to allocate it. If there is metaData to the right, we do not need to worry about.
                if (nextMDIndex + 8 <= MEMSIZE) { // If there is actually enough space to store this new metaData
                    md->available = TRUE;
                    md->dataSize = MEMSIZE - (x + (3 * sizeof(struct metaData)) + size); // How much memory there is left to allocate. Here, we are accounting for three metaData structs. The one made by user, the one storing how much data is left over, and space for the next metaData that will be stored on the next malloc call.
                } else {
                    noMoreMem(file, line);
                    return NULL;
                }
            }

            return &memory[x] + sizeof(struct metaData);
        } else {
            x += sizeof(struct metaData) + md->dataSize; // Iterate through array.
            continue;
        }
    }

    noMoreMem(file, line);
    return NULL;
}

/*
 * Myfree() (will be called by a call to free(), see mymalloc.h). This function will determine if *ptr is valid. If it is a valid pointer,
 * then it will go to the metaData that is stored behind it and set its available flag to true indicating the memory has been freed. Afterwards, we call coalesceBlocks()
 * to combine any two adjacent free blocks.
 */

void ufree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        nullPointerPassed(file, line);
        exit(1);
    }

    struct metaData *md = ((struct metaData *) ptr) - 1; // Finds the metaData that is behind the allocated memory.

    if (md->available == TRUE) { // Block has already been freed or has not been used yet.
        doubleFree(file, line);
        exit(1);
    } else if ((md->available != FALSE && md->available != TRUE) || md->dataSize <= 0) { // The user could malloc the exact contents of the metaData, basically emulating it and then try to free it, but even actual malloc and free has this vulnerability. The user can mess up their metaData. We are not in charge of that.
        wrongPointer(file, line);
        exit(1);
    } else {
        md->available = TRUE; // Free the memory and coalesce.
        coalesceBlocks();
    }
}

/*
 * Free all was a special function we produced to essentially avoid memoryLeaks and other common issues with unallocated memory.
 * If the user messes up their memory or something bad happens, or the user wants to make sure everything is freed at the end of their program,
 * they can call this simple function that will loop through the entire memory array and free everything inside. While this does have a performance cost,
 * it does greatly increase security (by making sure that the memory will be freed). If the user is calling this, it's more likely their memory management was sloppy,
 * or they do not care about performance. Either way, the option is there should the user need it, or if they need it for debugging purposes, or for quick programs.
 */

void freeAll() {
    struct metaData *md;
    for (int x = 0; x < MEMSIZE; x += sizeof(struct metaData *) + md->dataSize) {
        md = (struct metaData *) &memory[x];
        if (md->available == FALSE) {
            free(&memory[x + sizeof(struct metaData)]);
        }
    }

    coalesceBlocks();

    return;
}
