#include <string.h>
#include "decode.h"

uint16_t current_index = 0;
uint16_t treeSize;

void decode() {
	uint8_t trash_size;
	uint8_t* tree_str;
	uint8_t file_name_in[MAX_FILE_NAME_SIZE];
	
	uint8_t tree_info[2];
	
	printf("Digite o caminho completo do arquivo:\n"
		   "-> ");
	scanf("%s", file_name_in);
	
	FILE* file_in = fopen(file_name_in, "rb");
	
	fscanf(file_in, "%c", &tree_info[0]);
	fscanf(file_in, "%c", &tree_info[1]);
	
	treeSize = ((((uint8_t) (tree_info[0] << 3)) >> 3) << 8) | tree_info[1];
	trash_size = tree_info[0] >> 5;
	
	tree_str = (uint8_t*) malloc((treeSize * 2) + 1);
	uint16_t i;
	for (i = 0; i < treeSize; i++) {
		fscanf(file_in, "%c", tree_str + i);
		if ((tree_str[i] == '\\') && (tree_str[i - 1] != '\\')) {
			treeSize++; /** Compensando o \ na leitura da string!!*/
		}
	}
	tree_str[i] = '\0';
	
	huff_t* huff_root = create_huff_tree_from_str(tree_str);
	
	print_preorder(huff_root);
	
}

huff_t* create_huff_tree_from_str(const uint8_t* pre_order_str) {
	if (treeSize == current_index) {
		return NULL;
	}
	
	/** Cria o nó de huffman. */
	huff_t* new_node = (huff_t*) malloc(sizeof(huff_t));
	new_node->item = (uint8_t*) malloc(sizeof(uint8_t));
	new_node->freq = NULL;
	new_node->next = NULL;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	
	/** Seta o conteúdo do nó pra o char atual. */
	*(uint8_t*) new_node->item = *(pre_order_str + current_index);
	current_index++; /**< Avança na string. */
	
	/** Montando a árvore da pré-ordem. */
	if (*(uint8_t*) new_node->item == '*') { /**< Se é um nó interno, monta os seus filhos */
		new_node->left_child = create_huff_tree_from_str(pre_order_str);
		new_node->right_child = create_huff_tree_from_str(pre_order_str);
	} else if (CHECK_IS_CONTROL(new_node)) {
		/**
		 * Se leu um \, cria um nó de controle, e salva o caractere depois dele como seu filho da esquerda
		 * depois pula pro próximo char.
		 */
		
		huff_t* new_escaped_node = (huff_t*) malloc(sizeof(huff_t));
		new_escaped_node->item = (uint8_t*) malloc(sizeof(uint8_t));
		new_escaped_node->freq = NULL;
		new_escaped_node->next = NULL;
		new_escaped_node->left_child = NULL;
		new_escaped_node->right_child = NULL;
		
		*(uint8_t*) new_escaped_node->item = *(pre_order_str + current_index);
		new_node->left_child = new_escaped_node;
		current_index++; /**< Pula para o próximo char */
	}
	
	return new_node;
}