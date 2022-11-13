#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"

huff_t* create_huff_tree(priority_queue_t* priority_queue) {
	
	huff_t* huff_left = NULL;
	huff_t* huff_right = NULL;
	huff_t* huff_father = NULL;
	
	/*Soma das frequências dos dois nós desenfileirados.*/
	uint64_t freq_sum;
	
	while (priority_queue != NULL) {
		
		/*Desenfileira os dois nós com menos frequência.*/
		huff_left = dequeue(priority_queue);
		huff_right = dequeue(priority_queue);
		
		/*Soma a frequência dos dois nós desenfileirados.*/
		
		/* Asterisco para criar o pai. == 42 */
		uint8_t item = '*';
		
		//printf("Criando um pai para os bytes: %X e %X\n",*(unsigned char*)huff_left->item,*(unsigned char*)huff_right->item);
		
		freq_sum = 0;
		uint64_t freq_left = *(uint64_t*) (*(uint8_t*) huff_left->item == '\\' ? huff_left->left_child
																			   : huff_left)->freq;
		uint64_t freq_right = *(uint64_t*) (*(uint8_t*) huff_right->item == '\\' ? huff_right->left_child
																				 : huff_right)->freq;
		
		freq_sum = freq_left + freq_right;
		
		/*Se a árvore estiver vazia, cria um pai para os últimos dois nós e retorna essa pai como raiz da árvore.*/
		if (priority_queue->size == 0) {
			return create_huff_node(&item, freq_sum, huff_left, huff_right, false);
			
		}
		/* Caso o nó da direita seja não folha, e com mesma frequência do da esquerda, que é folha, coloca ele para esquerda */
		else if ((*(uint8_t*) huff_right->item == '*') && (*(uint8_t*) huff_left->item != '*') &&
				 (freq_left == freq_right)) {
			huff_father = create_huff_node(&item, freq_sum, huff_right, huff_left, false);
			enqueue(priority_queue, huff_father);
			
			
		} else { /* Caso padrão, enqueue na junção dos dois dequeues*/
			huff_father = create_huff_node(&item, freq_sum, huff_left, huff_right, false);
			enqueue(priority_queue, huff_father
			);
		}

/*Debugging da arvore.*/
/*printf("Essa e a fila depois das operações:\n");
print_queue(priority_queue);
printf("\n");*/
	}
	return
			huff_father;
	
}

void print_preorder(huff_t* root) {
	
	if (!is_tree_empty(root)) {
		if (*(uint8_t*) root->item == '*') {
			printf("%c ", *(uint8_t*) root->item);
		} else if (*(uint8_t*) root->item == '\\') {
			printf("(%c) ", *(uint8_t*) root->left_child->item);
		} else {
			printf("(%c) ", *(uint8_t*) root->item);
		}
		
		print_preorder(root->left_child);
		print_preorder(root->right_child);
	}
}

bool is_tree_empty(huff_t* root) {
	return root == NULL;
}

int tree_size(huff_t* root) {
	if (root == NULL) return 0;
	else return 1 + tree_size(root->left_child) + tree_size(root->right_child);
}