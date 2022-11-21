#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "umalloc.h"

#define LONG_TEST 0

int main() {
    int test0_success = 0;
    int test1_success = 0;
    int test2_success = 0;
    int test3_success = 0;
    int test4_success = 0;
    int test5_success = 0;
    srand(time(0));
    struct timeval start, end;



    // Test 0: Consistency
    // Allocate a small block (1B to 10B), case it to a type, write to it, free it
    // Allocate a block of the same size, cast it to the same type, then check to see if the address of the pointers are the same
    char * hello_string_1 = (char*) malloc(8*sizeof(char));
    hello_string_1[0] = 'H';
    hello_string_1[1] = 'e';
    hello_string_1[2] = 'l';
    hello_string_1[3] = 'l';
    hello_string_1[4] = '0';
    hello_string_1[5] = '\0';

    free(hello_string_1);

    char * hello_string_2 = (char*) malloc(8*sizeof(char));
    hello_string_2[0] = 'H';
    hello_string_2[1] = 'e';
    hello_string_2[2] = 'l';
    hello_string_2[3] = 'l';
    hello_string_2[4] = '0';
    hello_string_2[5] = '\0';

    free(hello_string_2);

    // If the two blocks pointed to the same address, then the test was successful
    if(hello_string_1 == hello_string_2){test0_success = 1;}



    // ---------------------------------------------------------------------------
    // Test 1: Maximization
    // Allocate 1 byte, if malloc doesn't return null, then free it.
    // Allocate 2 bytes, if malloc doesn't return null, then free it
    // so on ...
    // When malloc returns null, halve the size but don't free.
    // Then malloc with that size until it returns null, when it returns null then divde the size by 2
    // Keep doing this until the size is 1 and malloc returns null, this is the maximal allocation size


    int currentblocksize = 1;
    int max_allocation_size = 0;
    int max_reached = 0;

    while(1) {
        char* max_alloc = (char*) malloc(currentblocksize * sizeof(char));
        if (max_alloc == NULL) {
            if(currentblocksize == 1 || currentblocksize == 0) {
                break;
            }
            currentblocksize = currentblocksize / 2;
            max_reached = 1;
        }

        else {
            if(max_reached == 0) {
                free(max_alloc);
                currentblocksize = currentblocksize * 2;
            }
            else {
                if (max_allocation_size < currentblocksize) {
                    max_allocation_size = currentblocksize;
                }
            }
        }
    }
    freeAll();
    test1_success = 1;





    // ---------------------------------------------------------------------------
    // Test 2: Basic Coalescence:
    // Allocate 1/2 of your maximal allocation (found from Test 1)
    // Allocate one quarter of your maximal allocation
    // free the first pointer
    // free the second pointer
    // attempt to allocate your maximal allocation - it should work
    // free it

    char* half_alloc = (char*) malloc( (max_allocation_size / 2) * sizeof(char));
    char* quarter_alloc = (char*) malloc( (max_allocation_size / 4) * sizeof(char));
    free(half_alloc);
    free(quarter_alloc);
    char* max_alloc = (char*) malloc( (max_allocation_size) * sizeof(char));

    if(max_alloc != NULL){ test2_success = 1; }
    freeAll();




    // ---------------------------------------------------------------------------
    // Test 3: Saturation
    // Do 9k 1KB allocations (i.e. do 9216 1024 byte allocations)
    // Switch to 1B allocations until malloc responds with NULL, that is your saturation of space

    int maximal_number_of_allocations = 0;
    char* last_block_pointer = NULL;
    char* pointer_array[11000];
    int number_of_pointers = 0;

    for (int i = 0; i < 9216 ; i++) {
        pointer_array[i] = (char*) malloc(1024 * sizeof(char));
        number_of_pointers++;
    }

    while(1) {
        char* sat_pointer = (char*) malloc(1024 * sizeof(char));
        if(sat_pointer == NULL) {
            break;
        }
        pointer_array[number_of_pointers] = sat_pointer;
        number_of_pointers++;
        last_block_pointer = sat_pointer;
        maximal_number_of_allocations++;
    }

    test3_success = 3;




    // ---------------------------------------------------------------------------
    // Test 4: Time Overhead
    // Saturate your memory with 1B allocations (immediately from Test 3)
    // Free the last 1B block
    // Get the current time
    // Allocate 1B
    // Get the current time, compute the elapsed time, that is your max time overhead

    free(last_block_pointer);
    gettimeofday(&start, NULL);
    last_block_pointer = malloc(1 * sizeof(char));
    gettimeofday(&end, NULL);
    long double timeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec));
    test4_success = 1;




    // ---------------------------------------------------------------------------
    // Test 5: Intermediate Coalescence
    // Saturate your memory with 1B allocations
    // Free each one, one by one
    // Attempt to allocate your maximal allocation - it should work
    // Free all memory
    for(int i  = 0; i < number_of_pointers ; i++) {
        free(pointer_array[i]);
    }
    max_alloc = (char*) malloc(max_allocation_size * sizeof(char));

    if (max_alloc != NULL) {
        test5_success = 1;
    }




    printf("------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("\n");

    if (test0_success) {
        printf("Test #0: Consistency\n");
        printf("Instructions: Allocate a small block, cast it to a type and free it. Allocate a block of the same size, cast it to the same type, then check to see if the address of the pointers are the same\n");
        printf("Result: Success. After comparing the address of both pointers, both char pointers pointed to the same address\n");
        printf("------------------------------------------------------------------------------------\n");
    }

    if (test1_success) {
        printf("Test Case #1: Maximization\n");
        printf("Instructions: Allocate 1B, if the result is not NULL then free it, double the size and try again. On NULL, havlve the size and try again. On success after a NULL, stop.\n");
        printf("Results: Success. Max Allocation Size = %d B\n",max_allocation_size);
        printf("------------------------------------------------------------------------------------\n");
    }

    if (test2_success) {
        printf("Test Case #2: Basic Coalescence\n");
        printf("Instructions: Allocate one half of your maximal allocation size (from Test 1). Allocate one quarter of your maximal allocation size. Free the first pointer then the second pointer and attempt to allocate the maximal allocation size\n");
        printf("Results: Successfully allocated 1/2 of maximal allocation, successfully allocated 1/4 of maximal allocation, successfully freed both allocs, and successfully allocated maximal allocation\n");
        printf("------------------------------------------------------------------------------------\n");
    }

    if (test3_success) {
        printf("Test 3: Saturation\n");
        printf("Instructions: Do 9K 1KB allocations, then switch to 1B allocations until malloc responds with NULL, that is your saturation of space\n");
        printf("Results: Max Number of Allocations: %d\n",maximal_number_of_allocations);
        printf("------------------------------------------------------------------------------------\n");
    }


    if (test4_success) {
        printf("Test 4: Time Overhead\n");
        printf("Instructions: Saturate your memory (immediately after Test 3), free the last 1B block, get the current time, allocate 1B block and get the current time. Compute the elapsed time, that is your max time overhead\n");
        printf("Results: Max Time Overhead = %Lf ns\n",timeTaken);
        printf("------------------------------------------------------------------------------------\n");
    }

    if (test5_success) {
        printf("Test 5: Intermediate Overhead\n");
        printf("Instructions: Saturate your memory (i.e. immediately after Test 4), free each allocation and attempt to allocate your maximal allocation size. Then free all memory.\n");
        printf("Results: Memory was saturated, then each pointer was freed one by one and the maximal allocation was successfully allocated\n");
        printf("------------------------------------------------------------------------------------\n");
    }

    freeAll();


    if (LONG_TEST) {
        puts("\n\nPlease Note: The long test macro is defined. It will probably take close to 1500 seconds (30 minutes) to complete depending on the hardware.\n");
        printf("Allocating 1 Byte Chunks...\n\n");
        for (char *c = malloc(1); c != NULL; c = malloc(1)) {
            printf("Percentage of memory that has been allocated is %lf%%\r", (double) (1.00 - (double) currentMemAreaLeft / MEMSIZE) * 100.0);
        }

        puts("Percentage of memory that has been allocated is 100%");

        freeAllFast();
    }

    return 0;
}
