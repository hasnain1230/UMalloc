/*
 * Hasnain Ali (ha430)
 * Rushabh Patel (rsp155)
 * Della Maret (dm1379)
 * iLab Machine Tested On: ilab.cs.rutgers.edu and rlab1.cs.rutgers.edu
 */
#ifndef _ERRORS_H
#define _ERRORS_H

//prototypes of errors from errors.c
void doubleFree(char* file, int line);
void wrongPointer(char* file, int line);
void tooMuchMem(int MEMSIZE, char* file, int line, size_t structSize);
void noMoreMem(char* file, int line);
void mallocZeroError(char *file, int line);
void nullPointerPassed(char *file, int line);
void notEnoughFreeMemoryForAllocation(char *file, int line);
void enoughFreeMemoryButNoBlockLargeEnough(char *file, int line);

#endif