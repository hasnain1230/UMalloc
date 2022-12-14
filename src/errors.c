/*
 * Hasnain Ali (ha430)
 * Rushabh Patel (rsp155)
 * Della Maret (dm1379)
 * iLab Machine Tested On: ilab.cs.rutgers.edu and rlab1.cs.rutgers.edu
 */

#include <stdio.h>
#include "errors.h"

void doubleFree(char* file, int line) { //trying to free something you already freed
    printf("You cannot free something twice. [ %s:%d ]\n", file, line);
    return;
}

void wrongPointer(char* file, int line){ //client not giving right pointer to free mem (they are giving pointer that is not pointing at metadata for mem we want to free)
    printf("You are not giving the right pointer to free mem. [ %s:%d ]\n", file, line);
    return;
}

void tooMuchMem(int MEMSIZE, char* file, int line, size_t structSize) { //client requesting more than MEMSIZE. Also, this error will only be printed on the first call to malloc, before mem is initialized!
    printf("You are requesting too much mem. You can request at most %lu bytes. [ %s:%d ]\n", (MEMSIZE - (structSize * 2)), file, line); // We are subtracting 16 because on the FIRST call to malloc, two meta-data structs are made, leaving the user with MEMSIZE - 16 bytes left to allocate.
    return;
}

void noMoreMem(char* file, int line){ //client requested more mem but there is no longer enough free space to allocate mem, same as heap buffer overflow
    printf("Malloc was unable to find a block big enough for your call. [ %s:%d ]\n", file, line);
    return;
}

void mallocZeroError(char *file, int line) {
    printf("You cannot malloc zero bytes! Please think about your life choices and try again! [ %s:%d ] \n", file, line);
    return;
}

void nullPointerPassed(char *file, int line) {
    printf("You passed a NULL pointer to free. This is not allowed! [ %s:%d ] \n", file, line);
    return;
}

void notEnoughFreeMemoryForAllocation(char *file, int line) {
    printf("There mem is not currently full, but there is not enough space for your allocation. [ %s:%d ]\n", file, line);
}
void enoughFreeMemoryButNoBlockLargeEnough(char *file, int line) {
    printf("There is enough free mem, but no block large enough for your requested allocation. [ %s:%d ] \n", file, line);
}