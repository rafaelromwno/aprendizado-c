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

void* my_malloc(size_t size){
    BlockHeader* current = free_list;

    while (current != NULL) {

        if (current -> is_free && current -> size >= size + sizeof(BlockHeader)) {

            if (current -> size > size + sizeof(BlockHeader) + sizeof(BlockHeader)) {

                BlockHeader* new_block = (BlockHeader*)((char*)current + sizeof(BlockHeader) + size);   

                new_block -> size = current -> size - size - sizeof(BlockHeader);

                new_block -> is_free = 1;

                new_block -> next = current -> next;


                current -> size = size;
                current -> next = new_block;

            }

            current -> is_free = 0;

            return (void*)(current + 1);
        }
        
        current = current -> next;

    }

    return NULL;
}

void my_free(void* ptr){

    if (ptr == NULL) return;

    BlockHeader* header = (BlockHeader*)ptr - 1;
    header -> is_free = 1;

    printf("Bloco de %zu bytes liberado com sucesso!\n", header -> size);
}

int main() {
    init_heap();

    printf("Heap inicializada com %zu bytes livres\n", (void*)free_list->size);

    // Aloca um bloco de 500 bytes
    void* ptr1 = my_malloc(500);
    if (ptr1 != NULL) {
        printf("Bloco de 500 bytes alocado com sucesso!\n");
    } else {
        printf("Falha na alocação de 500 bytes.\n");
    }

    // Aloca um bloco de 300 bytes
    void* ptr2 = my_malloc(300);
    if (ptr2 != NULL) {
        printf("Bloco de 300 bytes alocado com sucesso!\n");
    } else {
        printf("Falha na alocação de 300 bytes.\n");
    }

    // Tenta alocar mais um bloco de 200 bytes
    void* ptr3 = my_malloc(200);
    if (ptr3 != NULL) {
        printf("Bloco de 200 bytes alocado com sucesso!\n");
    } else {
        printf("Falha na alocação de 200 bytes.\n");
    }

    return 0;
}
