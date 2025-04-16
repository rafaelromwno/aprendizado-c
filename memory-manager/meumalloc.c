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

        if (current -> is_free && current -> size >= size){

            current -> is_free = 0;

            return (void*)(current + 1);
        }
        
        current = current -> next;

    }

    return NULL;
}

int main() {
    
    init_heap();

    printf("Heap inicializada com %zu bytes livres\n", free_list->size);

    void* ptr1 = my_malloc(100);

    if(ptr1 != NULL) {

        printf("Bloco de 100 bytes alocado com sucesso!\n");

        char* texto = (char*)ptr1;  

        texto[0] = 'H';
        texto[1] = 'i';
        texto[2] = '\0';

        printf("Valor armazenado: %s\n", texto);

    } else {

        printf("Falha na alocação de 100 bytes.\n");

    }

    return 0;
}