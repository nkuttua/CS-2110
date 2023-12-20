#ifndef MALLOC_INFO_H
#define MALLOC_INFO_H

struct mallocinfo {
    void *ptr;
    size_t size;
    struct mallocinfo *next;
};

#endif