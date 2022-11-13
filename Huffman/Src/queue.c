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
		new_huff_freq = *(uint64_t*) ((*(uint8_t*) new_huff->item == '\\') ? new_huff->left_child
																		   : new_huff)->freq;
		head_freq = *(uint32_t*) ((*(uint8_t*) ((huff_t*) priority_queue->head)->item == '\\')
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
		/** Percorre a fila até chegar no final, ou o nó cuja próxima frequência é maior ou igual que à ser inserida */
		while ((current_node->next != NULL) && (new_huff_freq > (*(uint64_t*) (*(uint8_t*) current_node->item == '\\'
																			   ? current_node->left_child
																			   : current_node->next)->freq))) {
			current_node = current_node->next;
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
		if (*(uint8_t*) aux->item == '\\') {
			printf("%c ", *(uint8_t*) aux->left_child->item);
		} else {
			printf("%c ", *(uint8_t*) aux->item);
		}
		aux = aux->next;
	}
	
}

huff_t* create_huff_node(void* item, uint64_t freq, huff_t* left_child, huff_t* right_child, bool is_before_tree) {
	/*Faz um ponteiro guardar o endereço da alocação do nó.*/
	huff_t* new_huff = (huff_t*) malloc(sizeof(huff_t));
	new_huff->left_child = left_child;
	new_huff->right_child = right_child;
	new_huff->next = NULL;
	
	/*Faz o void* guardar o endereço da alocação de um uint8_t.*/
	new_huff->item = malloc(sizeof(uint8_t));
	new_huff->freq = malloc((sizeof(uint64_t)));
	
	/** Se lê: o conteúdo do item do nó recebe o valor do conteúdo do item do parâmetro */
	*(uint8_t*) new_huff->item = *(uint8_t*) item;
	*(uint64_t*) new_huff->freq = freq;
	
	/*Faz o item do nó alocado guardar o valor que está sendo apontado pelo item do parâmetro.*/
	if (is_before_tree && (*(uint8_t*) item == '\\' || *(uint8_t*) item == '*')) {
		/** Caso leia '\' ou '*', cria um nó de controle, com item '\' para ler o próximo nó como folha */
		huff_t* control_node = (huff_t*) malloc(sizeof(huff_t));
		control_node->left_child = new_huff;
		control_node->right_child = NULL;
		control_node->next = NULL;
		
		control_node->item = malloc(sizeof(uint8_t));
		*(uint8_t*) control_node->item = '\\';
		
		return control_node;
	}
	
	return new_huff;
}