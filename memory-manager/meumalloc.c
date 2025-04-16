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

    my_free(ptr1);

    return 0;
}