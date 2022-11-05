#include <stdio.h>
#include "queue.h"

priority_queue_t*create_priority_queue()
{
    priority_queue_t*new_queue = (priority_queue_t*) malloc(sizeof(priority_queue_t));
    new_queue->size = 0;
    return new_queue;
}
bool is_empty(priority_queue_t* priority_queue) {
    return priority_queue->head == NULL;
}

void enqueue(priority_queue_t* priority_queue, void* item, uint64_t freq) {

    
    /** Cria um nó de huffman */
    huff_t* new_huff = (huff_t*) malloc(sizeof(huff_t));
    new_huff->down_left = NULL;
    new_huff->down_right = NULL;
    new_huff->item = (unsigned char*) malloc(sizeof(unsigned char));;
    *(unsigned char *)new_huff->item = *(unsigned char*)item;
    new_huff->freq = freq;

    /** Cria um nó da fila de prioridades de nós de huffman */
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->value = new_huff;
    

    /** Insere o nó de forma crescente */
    if ((is_empty(priority_queue)) || (freq <= priority_queue->head->value->freq)) { /** < Não precisa andar pela fila */
        new_node->next = priority_queue->head;
        priority_queue->head = new_node;
        priority_queue->size++;
    } else { /** < Percorre a fila até chegar no final, ou o nó cuja próxima frequência é maior ou igual que à ser inserida */
        node_t* current_node = priority_queue->head;
        while ((current_node->next != NULL) && (freq > current_node->next->value->freq)) {
            current_node = current_node->next;
        }

        /** Insere o nó e incrementa o tamanho da fila*/
        new_node->next = current_node->next;
        current_node->next = new_node;
        priority_queue->size++;
    }
}
node_t* dequeue(priority_queue_t *priority_queue)
{
    /**Verifica se a fila está vazia.*/
    if (is_empty(priority_queue)) {
        printf("Priority Queue underflow\n");
        return NULL;
    } 
    else {/*Se a fila não estiver vazia, a função remove o nó que está na cabeça.*/
        node_t *node = priority_queue->head;
        priority_queue->head = priority_queue->head->next;
        node->next = NULL;
        priority_queue->size--;
        return node;
    }
}
void print_queue(priority_queue_t* priority_queue)
{
    /**Cria um ponteiro auxiliar, que recebe o endereço da cabeça da fila, para navegar pela fila até o último elemento. */
    node_t *aux = priority_queue->head;
    
    /*Imprime o byte na tela, representando-o como um unsigned char;*/
        for (int i = 0; i < priority_queue->size;i++ ){
            printf("%X ",*(unsigned char*)aux->value->item);
            aux = aux->next;
        }
        
    
}