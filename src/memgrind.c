#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "umalloc.h"

int main() {
    srand(time(0));
    
    struct timeval start, end;

    // Test 1: Malloc and immediately free a 1 byte chunk 120 times. Repeat this 50 times.
    // ============================================================================================================
    gettimeofday(&start, NULL);

    for(int i = 0; i<50; i++){ 
        for (int j = 0; j<120; j++){
            char *c = malloc(1);

            if (c == NULL) {
                perror("Malloc Returned NULL. Please see error message above. Program is exiting...");
                exit(1);
            }

            free(c);
        }
    }

    gettimeofday(&end, NULL);

    long double averageTimeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec)) / 50.0;

    printf("Test 1: This test is where we malloc 1 byte, and then free it. We do this 120 times. We repeated this 50 times as expressed in the instructions.\n");
    printf("On average, it took about %Lf microseconds to complete this test: \n\n\n", averageTimeTaken);
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================



    // Test 2: Use Malloc to get 120, 1 byte chunks, store the pointers in an array, then use free to deallocate those chunks. Repeat this test 50 times.
    // ============================================================================================================
    gettimeofday(&start, NULL);

    for(int i = 0; i<50; i++){
        char *test1 = malloc(120);

        if (test1 == NULL) {
            perror("Malloc Returned NULL. Please see error message above. Program is exiting...");
            exit(1);
        }

        char *test2[120];

        for (int j = 0; j<120; j++){
            test2[j] = &test1[j];
        }

		unusedFunction(test2); // This function was made to supress the unused variable warning in the -Wextra flag we are compiling with. Please ignore this. 

        free(test1);
    }
	
    gettimeofday(&end, NULL);

    averageTimeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec)) / 50.0;

    printf("Test 2: This test is where we malloc 120, 1 byte chunks, and store the corresponding pointer returned in a separate array that we statically define. We repeated this 50 times as expressed in the instructions.\n");
    printf("On average, it took about %Lf microseconds to complete this test (this includes the calls to unusedFunction() that was made to supress unused variable warnings in this test): \n\n\n", averageTimeTaken);

    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================





    // Test 3: Randomly choose between allocating a 1-byte chunk and storing it in an array and deallocating one of the chunks in the array if any exist. Repeat until
    //         malloc was called 120 times, then free all remaining allocated chunks. Repeat this test 50 times.
    // ============================================================================================================
    //gettimeofday(&start, NULL);

    int malloc_called = 0;
    void *pointerArr[120]; // Pointer Array

    for (int x = 0; x < 50; x++) {
        while (malloc_called < 120) {
            int randomNum = rand() % 2;

            if (randomNum == 0) {
                char *chunk = malloc(1);

                if (chunk == NULL) {
                    perror("Malloc Returned NULL. Please see error message above. Program is exiting...");
                    exit(1);
                }

                pointerArr[malloc_called] = chunk; // Store the pointer that malloc returned, in the pointer array.
                malloc_called++;
                continue;
            } else { // Otherwise, we randomly free one of the chunks as specified in one of the test cases.
                for (int y = 0; y < malloc_called && pointerArr[y] != NULL; y++) { // If there is something to actually deallocate, hence the condition.
                    free(pointerArr[y]);
                    pointerArr[y] = NULL;
                }
            }
        }

        for (int z = 0; z < malloc_called; z++) { // This loop frees everything else in the array.
            if (pointerArr[z] != NULL) {
                free(pointerArr[z]);
            }
        }

        malloc_called = 0;
    }

    gettimeofday(&end, NULL);

    averageTimeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec)) / 50.0;

    printf("Test 3: This test is where we randomly choose between allocating a 1-byte chunk and storing the pointer in an array OR deallocating one of the chunks in the aforementioned array, if any exist. We repeated this 50 times as expressed in the instructions.\n");
    printf("On average, it took about %Lf microseconds to complete this test. \n\n\n", averageTimeTaken);

    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================


    // Test 4: Create a randomly sized array n, with integers. This n-sized array will be between size 1 and size 120. Then, fill this array up with integers between 0 and n. Free the entire array.
    //         Repeat this 50 times.
    // ============================================================================================================

    gettimeofday(&start, NULL);

    for (int i = 0; i < 50; i++) {
        int *array = (int *) malloc (120 * sizeof(int)); // Make Array of size 120.

        if (array == NULL) {
            perror("Malloc Returned NULL. Please see error message above. Program is exiting...");
            exit(1);
        }

        for (int j = 0; j < 120; j++) { // fill array with items
            array[j] = j;
        }

        free(array);
    }

    gettimeofday(&end, NULL);

    averageTimeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec)) / 50.0;
    printf("Test 4: This test is where we created an array of size 120 and filled it with integers followed by freeing it.\n");
    printf("This test is repeated 50 times as expressed in the instructions.\n");
    printf("On average, it took %Lf microseconds for each of these tasks to complete.\n\n\n", averageTimeTaken);

    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================


    // Test 5: Create a 10x12 2D Array. Fill it up with random integers.
    //         Repeat this 50 times.
    // ============================================================================================================

    gettimeofday(&start, NULL);

    for (int x = 0; x < 50; x++) {
        int **array = (int **) malloc(10 * sizeof(int *)); // Allocate rows of the array.

        for (int y = 0; y < 10; y++) {
            array[y] = (int *) malloc(12 * sizeof(int)); // Allocate columns of the array.
        }

        for (int r = 0; r < 10; r++) {
            for (int c = 0; c < 12; c++) {
                array[r][c] = rand() % RAND_MAX; // Fill it up with random integers.
            }
        }

        for (int i = 0; i < 10; i++) {
            free(array[i]); // Free everything.
        }

        free(array); // Free array.
    } // Repeat this 50 times.

    gettimeofday(&end, NULL);

    averageTimeTaken = (((long double) end.tv_usec) - ((long double) start.tv_usec)) / 50.0;
    printf("Test 5: This test is where we created a 2D array and filled it with random integers between 0 and RAND_MAX.\n");
    printf("This test is repeated 50 times as expressed in the instructions.\n");
    printf("On average, it took %Lf microseconds for each of these tasks to complete.\n\n", averageTimeTaken);

    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================

    return 0;
}
