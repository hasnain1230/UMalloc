#ifndef _ERRORS_H
#define _ERRORS_H

//prototypes of errors from errors.c
void doubleFree(char* file, int line);
void wrongPointer(char* file, int line);
void tooMuchMem(int MEMSIZE, char* file, int line, size_t structSize);
void noMoreMem(char* file, int line);
void mallocZeroError(char *file, int line);
void nullPointerPassed(char *file, int line);

#endif