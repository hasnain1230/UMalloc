#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "umalloc.h"

struct metaData {
    char available; // In this case, available will either be set as T or F for true or false.
    unsigned short dataSize; // We did not use size_t here to save space in the long run. Rather than having a 16 byte alignment, doing unsigned int makes it 8 byte aligned which will save space. I think it is safe to assume that the user will not be allocating more than 4 GB of memory all at once should the memory be 2^32 bytes large.
};

int main(void) {
    int *p = malloc(4096);
}