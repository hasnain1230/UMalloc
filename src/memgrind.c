#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "umalloc.h"

void unusedFunction(char **arr) { // This is done to supress unused variable error provided in the -Wextra flag that we are using.
	arr = arr;
	return;
}

int main() {
    srand(time(0));
    
    struct timeval start, end;


    // Test 0: Consistency
    // Allocate a small block (1 to 10B), case it to a type, write to it, free it
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

    if(hello_string_1 == hello_string_2){
        printf("Test #0: Consistency\n");
        printf("In this test a small block was allocated, casted to char*, written to and then freed\n");
        printf("Next another block was of the same size and same type was allocated and written to and then freed\n");
        printf("Result: After comparing the pointers, both char* pointed to the same address\n");
        printf("------------------------------------------------------------------------------------\n");
    }









    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    // Test 1: Maximization
    // Allocate 1B, if the result is not NULL, free it, double the size and try again
    // on NULL, half the size and try again
    // if NULL and size is 1 or 0, that is your maximal allocation
    // free it
    int currentblocksize = 1;
    int max_allocation_size = 0;

    while(0) {

        char* max_alloc = (char*) malloc(currentblocksize);

        if (max_alloc == NULL) {
            printf("Alloc block size was too big,");
            if (currentblocksize == 1 || currentblocksize == 0) {
                break;
            }
            printf(" halving the currentblocksize (currentblocksize = %d)\n",currentblocksize);
            free(max_alloc);
            currentblocksize = currentblocksize / 2;


        }

        else {
            printf("Alloc block size wasn't big enough, doubling the currentblock size (currentblocksize = %d)\n",currentblocksize);
            free(max_alloc);
            max_allocation_size = currentblocksize;
            currentblocksize = currentblocksize * 2;


        }


    }

    printf("Test Case #1: Maximization\n");
    printf("Results: Max Number of Allocations = %d\n",max_allocation_size);
    printf("-----------------------------------------------------------------------------------------------\n");




    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    // Test 2: Basic Coalescence:
    // Allocate 1/2 of your maximal allocation
    // Allocate one quarter of your maximal allocation
    // free the first pointer
    // free the second pointer
    // attemp to allocate your maximal allocation - it should work
    // free it







    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    // Test 3: Saturation
    // Allocated 1B
    // Continue allocation 1B until malloc responds with NULL, that is your maximal number of allocations

    int maximal_number_of_allocations = 0;
    char* last_block_pointer = null;

    while(1) {

        last_block_pointer = (char*) malloc(1 * sizeof(char));

        if(last_block_pointer == NULL) {
            break;
        }

        maximal_number_of_allocations++;
    }



    printf("Test 3: Saturation\n");
    printf("In this test 1B was initially allocated, then we continuted allocating 1B until malloc returned NULL and the number of times we were able to allocate was the max number of allocations\n");
    printf("Results: Max Number of Allocations: %d\n",maximal_number_of_allocations);
    printf("------------------------------------------------------------------------------------\n");   




    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    // Test 4: Time Overhead
    // Saturate your memory with 1B allocations (continue from Test 3)
    // Free the last 1B block
    // get the current time
    // allocate 1B
    // get the current time, compute the elapsed time, that is your max time overhead

    free(last_block_pointer);
    gettimeofday(&start, NULL);
    last_block_pointer = malloc(1 * sizeof(char));
    gettimeofday(&end, NULL);

    long double timeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec));


    printf("Test 4: Time Overhead\n");
    printf("In this test the memory was saturated with 1B allocations (from Test 3), the last 1B block was freed and allocated again. We timed the elapsed time it took to allocate the 1B block again\n");
    printf("Results: Max Time Overhead = %Lf ns\n",timeTaken);
    printf("------------------------------------------------------------------------------------\n");



    
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------
    // Test 5: Intermediate Coalescence
    // Saturate your memory with 1B allocations 
    // Free each one, one by one
    // Attempt to allocate your maximal allocation - it should work
    // Free all memory


    
    return 0;
}
