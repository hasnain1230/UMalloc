#include <stdio.h>
#include "errors.h"

void doubleFree(char* file, int line){//trying to free something you already freed
    printf("You cannot free something twice. [ %s:%d ]\n", file, line);
    return;
}

void wrongPointer(char* file, int line){ //client not giving right pointer to free memory (they are giving pointer that is not pointing at metadata for memory we want to free)
    printf("You are not giving the right pointer to free memory. [ %s:%d ]\n", file, line);
    return;
}

void tooMuchMem(int MEMSIZE, char* file, int line, size_t structSize) { //client requesting more than MEMSIZE. Also, this error will only be printed on the first call to malloc, before memory is initialized!
    printf("You are requesting too much memory. You can request at most %lu bytes. [ %s:%d ]\n", (MEMSIZE - (structSize * 2)), file, line); // We are subtracting 16 because on the FIRST call to malloc, two meta-data structs are made, leaving the user with MEMSIZE - 16 bytes left to allocate.
    return;
}

void noMoreMem(char* file, int line){ //client requested more memory but there is no longer enough free space to allocate mem, same as heap buffer overflow
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