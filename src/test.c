#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "umalloc.h"

int main() {
    size_t x = 1;
    size_t totalAllocated = 0;
    char *test1 = malloc(x);

    while (test1 != NULL) {
        free(test1);
        test1 = malloc(x * 2);

        if (test1 != NULL) {
            x *= 2;
        }
    }

    while (1) {
        test1 = malloc(x);

        if (test1 == NULL) {
            if (x == 1 || x == 0) {
                break;
            }
            x /= 2;
        } else {
            totalAllocated += x;
        }
    }

    while (1) {
        test1 = malloc(x);

        if (test1 != NULL) {
            totalAllocated += x;
            continue;
        } else if (test1 == NULL) {
            if (x == 1) {
                break;
            }
            x /= 2;
        }
    }

    printf("Total Allocated: %zu\n", totalAllocated);

    freeAll();

    return 0;
}
