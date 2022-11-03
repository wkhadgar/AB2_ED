#include "queue.h"

bool is_empty(priority_queue_t* priority_queue) {
    return priority_queue->head == NULL;
}

void enqueue(priority_queue_t* priority_queue, void* item, uint64_t freq) {

    /** Cria um nó de huffman */
    huff_t* new_huff = (huff_t*) malloc(sizeof(huff_t));
    new_huff->down_left = NULL;
    new_huff->down_right = NULL;
    new_huff->item = item;
    new_huff->freq = freq;

    /** Cria um nó da fila de prioridades de nós de huffman */
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->value = new_huff;
    new_node->next = NULL;

    /** Insere o nó de forma crescente */
    if ((is_empty(priority_queue)) || (freq <= priority_queue->head->value->freq)) { /** < Não precisa andar pela fila */
        new_node->next = priority_queue->head;
        priority_queue->head = new_node;
    } else { /** < Percorre a fila até chegar no final, ou o nó cuja próxima frequência é maior ou igual que à ser inserida */
        node_t* current_node = priority_queue->head;
        while ((current_node->next != NULL) && (freq > current_node->next->value->freq)) {
            current_node = current_node->next;
        }

        /** Insere o nó */
        new_node->next = current_node->next;
        current_node->next = new_node;
    }
}