#include "huff_defines.h"

huff_t* create_huff_node(void* item, uint64_t freq, huff_t* left_child, huff_t* right_child, bool is_before_tree) {
	/*Faz um ponteiro guardar o endereço da alocação do nó.*/
	huff_t* new_huff = (huff_t*) malloc(sizeof(huff_t));
	new_huff->left_child = left_child;
	new_huff->right_child = right_child;
	new_huff->next = NULL;
	
	/*Faz o void* guardar o endereço da alocação de um uint8_t.*/
	new_huff->item = malloc(sizeof(uint8_t));
	new_huff->freq = malloc((sizeof(uint64_t)));
	
	/**
	 * Faz o item do nó alocado guardar o valor que está sendo apontado pelo item do parâmetro
	 * Se lê: o conteúdo do item do nó recebe o valor do conteúdo do item do parâmetro
	 */
	*(uint8_t*) new_huff->item = *(uint8_t*) item;
	*(uint64_t*) new_huff->freq = freq;
	
	if (is_before_tree && (*(uint8_t*) item == '\\' || *(uint8_t*) item == '*')) {
		/**
		 * Caso leia '\' ou '*' durante a montagem da fila de prioridades,
		 * cria um nó de controle, apenas com item '\' e filho da esquerda sendo a folha alvo.
		 *
		 * Sempre que lermos o '\' na arvore, usamos os valores do seu filho da esquerda como uma folha.
		 */
		huff_t* control_node = (huff_t*) malloc(sizeof(huff_t));
		control_node->item = malloc(sizeof(uint8_t));
		*(uint8_t*) control_node->item = '\\';
		control_node->right_child = NULL;
		control_node->next = NULL;
		control_node->freq = NULL;
		
		control_node->left_child = new_huff;
		return control_node;
	}
	
	return new_huff;
}