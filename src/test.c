#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "umalloc.h"

void unusedFunction(char **arr) { // This is done to supress unused variable error provided in the -Wextra flag that we are using.
    arr = arr;
    return;
}

int main() {
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

    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================
    // ============================================================================================================


    // Test 5: Create a 10x12 2D Array. Fill it up with random integers.
    //         Repeat this 50 times.
    // ============================================================================================================


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
    return 0;
}