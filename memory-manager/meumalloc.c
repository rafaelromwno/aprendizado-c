#include <stdio.h>
#include <stddef.h>

#define HEAP_SIZE 1024 * 1024 

char heap[HEAP_SIZE]; 

typedef struct BlockHeader {
    size_t size;
    int is_free;
    struct BlockHeader* next;
} BlockHeader;

BlockHeader* free_list = NULL;