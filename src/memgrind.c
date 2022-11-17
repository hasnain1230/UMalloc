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

    /*0. Consistency:
            allocate a small block (1 to 10B), cast it to a type, write to it, free it
            allocate a block of the same size, cast it to the same type, then check to see if the address of the pointers are the same*/
    
    printf("===================================================================================\nTest 0\n");

    int *test1 = malloc(4);
    ((char *)test1)[0] = 'h';
    ((char *)test1)[1] = 'i';
    ((char *)test1)[2] = '!';
    ((char *)test1)[3] = '\0';

    char *test2 = malloc(4);
    ((char *)test2)[0] = 'h';
    ((char *)test2)[1] = 'i';
    ((char *)test2)[2] = '!';
    ((char *)test2)[3] = '\0';
    
    // printf("%s\n", (char *)test1);
    // printf("%s\n", (char *)test2);
    printf("Address of test1 : %p\n", &test1);
    printf("Address of test2 : %p\n", &test2);

    free(test1);
    free(test2);
    freeAll();
    
    /* 1. Maximization:
            allocate 1B, if the result is not NULL, free it, double the size and try again
            on NULL, halve the size and try again
            if NULL and size is 1 or 0, that is your maximal allocation
            free it*/
    
    printf("===================================================================================\nTest 1\n");

    char *p;
    int allocated = 0;
    int size = 1;
    

    p = malloc(size);
    allocated = allocated + size;

    while(p != NULL){
        free(p);
        size = size*2;
        // printf("size: %d\n", size);
        p = malloc(size);
        allocated = allocated + size;
        // printf("allocated = %d\n", allocated);
    }

    //not sure if this is right, but once you hit NULL, then keep dividing the size

    while(1){
        size = size/2;
        if(size == 0 || size == 1){
            allocated = allocated + size;
            break;
        }else{
            // printf("size: %d\n", size);
            p = malloc(size);
            allocated = allocated + size;
            free(p);
        }
    }

    printf("allocated: %d\n", allocated);
    freeAll();

    /* 2. Basic Coalescence:
            allocate one half of your maximal allocation (see test 1)
            allocate one quarter of your maximal allocation
            free the first pointer
            free the second pointer
            attempt to allocate your maximal allocation - it should work
            free it*/
    
    printf("===================================================================================\nTest 2\n");

    //Test 2 works, just got to fix Test 1.
    /*
    int *ptr = malloc(allocated/2);
    int *ptr2 = malloc(allocated/4);

    free(ptr);
    free(ptr2);

    int *ptr3 = malloc(allocated);
    free(ptr3);
    */
    freeAll();

    /*3. Saturation:
            allocate 1B
            continue allocation 1B until malloc responds with NULL, that is your maximal number of allocations*/

    printf("===================================================================================\nTest 3\n");

    char *test3[100];
    int i = 0;
    while(i < 100){
        test3[i] = malloc(1);
        i++;
    }
    printf("i = %d\n", i);
    freeAll();

    /*4. Time Overhead:
            saturate your memory with 1B allocations (i.e. immediately after test 3)
            free the last 1B block
            get the current time
            allocate 1B
            get the current time, compute the elapsed time, that is your max time overhead*/
    
    printf("===================================================================================\nTest 4\n");

    clock_t start, end;

    int *test4[100];

    for(int i = 0; i < 100; i++){
        test4[i] = malloc(1);
    }
    free(test4[99]);

    start = clock();
    test4[99] = malloc(1);
    end = clock();

    double duration = (double)(end-start) / CLOCKS_PER_SEC;
    printf("max time overhead: %f seconds\n", duration);

    /*5. Intermediate Coalescence
            saturate your memory with 1B allocations (i.e. immediately after test 4)
            free each one, one by one
            attempt to allocate your maximal allocation - it should work
            free all memory*/

    
    return 0;
}
