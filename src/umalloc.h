#ifndef _UMALLOC_H
#define _UMALLOC_H

#define MEMSIZE (1024 * 1024 * 10)

#define malloc(s) umalloc(s, __FILE__, __LINE__)
#define free(p) ufree(p, __FILE__, __LINE__)

void *umalloc(size_t size, char *file, int line);
void ufree(void *ptr, char *file, int line);
void freeAll();
void printMemory(int bytes);

#endif
