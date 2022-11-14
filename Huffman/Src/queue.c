#include <stdio.h>
#include "queue.h"

priority_queue_t* create_priority_queue() {
	priority_queue_t* new_queue = (priority_queue_t*) malloc(sizeof(priority_queue_t));
	new_queue->size = 0;
	new_queue->head = NULL;
	return new_queue;
}

bool is_empty(priority_queue_t* priority_queue) {
	return priority_queue->head == NULL;
}

void enqueue(priority_queue_t* priority_queue, huff_t* new_huff) {
	uint64_t new_huff_freq;
	uint64_t head_freq;
	
	if (priority_queue->head != NULL) {
		new_huff_freq = *(uint64_t*) (CHECK_IS_CONTROL(new_huff) ? new_huff->left_child
																 : new_huff)->freq;
		head_freq = *(uint32_t*) (CHECK_IS_CONTROL(((huff_t*) priority_queue->head))
								  ? ((huff_t*) priority_queue->head)->left_child
								  : ((huff_t*) priority_queue->head))->freq;
	}
	
	/** Insere o nó de forma crescente */
	if (is_empty(priority_queue) || (new_huff_freq <= head_freq)) {
		new_huff->next = priority_queue->head;
		priority_queue->head = new_huff;
		priority_queue->size++;
	} else {
		huff_t* current_node = (huff_t*) priority_queue->head;
		/** Percorre a fila até chegar no final, ou enquanto o novo nó tem frequência maior que o próximo */
		while ((current_node->next != NULL) &&
			   (new_huff_freq > *(uint64_t*) ((*(uint8_t*) current_node->next->item == '\\')
											  ? current_node->next->left_child
											  : current_node->next)->freq)) {
			current_node = current_node->next; /**< Avança para o próximo nó */
		}
		
		/** Insere o nó e incrementa o tamanho da fila*/
		new_huff->next = current_node->next;
		current_node->next = new_huff;
		priority_queue->size++;
	}
}

huff_t* dequeue(priority_queue_t* priority_queue) {
	/**Verifica se a fila está vazia.*/
	if (is_empty(priority_queue)) {
		printf("Priority Queue underflow\n");
		return NULL;
	} else {/*Se a fila não estiver vazia, a função remove o nó que está na cabeça.*/
		priority_queue->size--;
		huff_t* node = (huff_t*) priority_queue->head;
		priority_queue->head = (huff_t*) ((huff_t*) (priority_queue->head))->next;
		node->next = NULL;
		return node;
	}
}

void print_queue(priority_queue_t* priority_queue) {
	/**Cria um ponteiro auxiliar, que recebe o endereço da cabeça da fila, para navegar pela fila até o último elemento. */
	huff_t* aux = priority_queue->head;
	
	/*Imprime o byte na tela, representando-o como um uint8_t;*/
	for (int i = 0; i < priority_queue->size; i++) {
		printf("'%c' ", *(uint8_t*) (CHECK_IS_CONTROL(aux) ? aux->left_child : aux)->item);
		aux = aux->next;
	}
	
}