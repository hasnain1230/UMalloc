#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "umalloc.h"

int main() {
    int *x = malloc(4);
    int *y = malloc(4);
    *y = 2;

    free(x);
    short *z = malloc(2);

    printMemory(128);
    printf("%d\n", *y);
}