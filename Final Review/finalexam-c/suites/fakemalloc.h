#include <stddef.h>
#ifndef FAKE_MALLOC_H
#define FAKE_MALLOC_H

void *fakemalloc(size_t);
void *fakecalloc(size_t, size_t);
void *fakerealloc(void*, size_t);


#define malloc(n)      fakemalloc(n)
#define calloc(n,s)    fakecalloc(n,s)
#define realloc(ptr,n) fakerealloc(ptr,n)

#endif