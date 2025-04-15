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

void init_heap(){
    free_list = (BlockHeader*)heap;
    free_list->size = HEAP_SIZE - sizeof(BlockHeader);
    free_list->is_free = 1;
    free_list->next = NULL;
}

int main() {
    
    init_heap();
    
    printf("Heap inicializada com %zu bytes livres\n", free_list->size);
    printf("Bloco livre? %s\n", free_list->is_free ? "Sim" : "Não");

    return 0;
}