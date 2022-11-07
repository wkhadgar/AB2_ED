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

void enqueue(priority_queue_t* priority_queue,huff_t* new_huff) {

    
    /** Cria um nó de huffman */
    //huff_t* new_huff = create_huff_node(item,freq);
    

    /** Cria um nó da fila de prioridades de nós de huffman */
    //node_t* new_huff = (node_t*) malloc(sizeof(node_t));
    //new_huff->value = new_huff;
    

    /** Insere o nó de forma crescente */
    if ((is_empty(priority_queue)) || (new_huff->freq <= priority_queue->head->freq)) { /** < Não precisa andar pela fila */
        new_huff->next = priority_queue->head;
        priority_queue->head = new_huff;
        priority_queue->size++;
    } else { /** < Percorre a fila até chegar no final, ou o nó cuja próxima frequência é maior ou igual que à ser inserida */
        huff_t* current_node = priority_queue->head;
        while ((current_node->next != NULL) && (new_huff->freq > current_node->next->freq)) {
            current_node = current_node->next;
        }

        /** Insere o nó e incrementa o tamanho da fila*/
        new_huff->next = current_node->next;
        current_node->next = new_huff;
        priority_queue->size++;
    }
}
huff_t* dequeue(priority_queue_t *priority_queue)
{
    /**Verifica se a fila está vazia.*/
    if (is_empty(priority_queue)) {
        printf("Priority Queue underflow\n");
        return NULL;
    } 
    else {/*Se a fila não estiver vazia, a função remove o nó que está na cabeça.*/
        huff_t *node = priority_queue->head;
        priority_queue->head = priority_queue->head->next;
        node->next = NULL;
        priority_queue->size--;
        return node;
    }
}
void print_queue(priority_queue_t* priority_queue)
{
    /**Cria um ponteiro auxiliar, que recebe o endereço da cabeça da fila, para navegar pela fila até o último elemento. */
    huff_t *aux = priority_queue->head;
    
    /*Imprime o byte na tela, representando-o como um unsigned char;*/
        for (int i = 0; i < priority_queue->size;i++ ){
            printf("%X ",*(unsigned char*)aux->item);
            aux = aux->next;
        }
        
}

huff_t* create_huff_node(void*item, int freq, huff_t* left_child, huff_t* right_child)
{
    /*Faz um ponteiro guardar o endereço da alocação do nó.*/
    huff_t* new_huff = (huff_t*) malloc(sizeof(huff_t));
    new_huff->down_left = left_child;
    new_huff->down_right = right_child;
    
    /*Faz o void* guardar o endereço da alocação de um unsigned char.*/
    new_huff->item = (unsigned char*) malloc(sizeof(unsigned char));
    
    /*Faz a alocação guardar o valor que está sendo apontado pelo parâmetro.*/
    *(unsigned char *)new_huff->item = *(unsigned char*)item;
    new_huff->freq = freq;
    return new_huff;
}