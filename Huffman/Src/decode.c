#include <string.h>
#include "decode.h"

/**
 * @brief Máscara para os últimos 5 bits.
 */
#define LAST_FIVE_BITS 0b00011111

/**
 * @brief Máscara para os primeiros 3 bits.
 */
#define FIRST_THREE_BITS 0b11100000

uint16_t current_index = 0;
uint16_t treeSize;

function_retval_t decode() {
	int32_t input;
	uint16_t j;
	uint64_t file_size;
	uint8_t trash_size;
	uint8_t file_name_in[MAX_FILE_NAME_SIZE];
	uint8_t file_name_out[MAX_FILE_NAME_SIZE];
	
	current_index = 0;
	treeSize = 0;
	
	uint8_t tree_info[2];
	uint8_t* tree_str;
	
	/** Enfeite visual */
	{
		presentation();
		printf("\n"
			   "Descodificacao selecionada!\n");
	}
	printf("\n"
		   "Digite o caminho completo do arquivo a ser descodificado:\n"
		   "-> ");
	scanf("%s", file_name_in);
	
	FILE* file_in = fopen(file_name_in, "rb");
	
	printf("Digite o nome do arquivo de saida, com sua extensao:\n"
		   "-> ");
	scanf("%s", file_name_out);
	
	FILE* file_out = fopen(file_name_out, "wb");
	
	
	if ((file_in == NULL) || fscanf(file_in, "%c", &tree_info[0]) == EOF) {
		printf("Nome de arquivo invalido, ou o arquivo nao foi encontrado. O que fazer?\n"
			   "[1] - Tentar descodificar novamente...\n"
			   "[2] - Retornar para o menu.\n"
			   "-> ");
		
		scanf("%d", &input);
		if (input == 1) {
			return DECODE_REPEAT;
		} else if (input == 2) {
			return DECODE_CANCEL;
		}
	}
	
	fscanf(file_in, "%c", &tree_info[1]);
	
	treeSize = ((((uint16_t) (tree_info[0])) & LAST_FIVE_BITS) << 8) | (uint16_t) tree_info[1];
	trash_size = (tree_info[0] & FIRST_THREE_BITS) >> 5;
	
	tree_str = (uint8_t*) malloc(treeSize + 3); /* No máximo mais 2 de escape, mais um de fim de string. */
	for (j = 0; j < treeSize; j++) {
		fscanf(file_in, "%c", &tree_str[j]);
#ifdef TREE_TRUE_SIZE
		if ((tree_str[j] == '\\') && (tree_str[j - 1] != '\\')) {
			treeSize++; /** Compensando o \ na leitura da string!!*/
		}
#endif
	}
	tree_str[j] = '\0';
	
	huff_t* huff_root = create_huff_tree_from_str(tree_str);
	
	//print_preorder(huff_root);
	
	uint16_t file_offset = ftell(file_in); /**< Guardar a posição atual no arquivo. */
	fseek(file_in, 0L, SEEK_END); /**< Vai para o último byte. */
	file_size = ftell(file_in);
	file_size -= file_offset; /**< Encontra o tamanho do arquivo, em termos de codificação. */
	fseek(file_in, file_offset, SEEK_SET); /**< Volta para onde começamos. */
	
	uint8_t current_file_byte, cr;
	huff_t* current_huff_node = huff_root;
	while (file_size-- > 1) {
		fscanf(file_in, "%c", &current_file_byte);
		for (uint8_t  i = 0; i < 8; i++) {
			if (CHECK_IS_CONTROL(current_huff_node)) {
				fputc(*(uint8_t*) current_huff_node->left_child->item, file_out);
				current_huff_node = huff_root;
			} else if (current_huff_node->left_child == NULL && current_huff_node->right_child == NULL) {
				fputc(*(uint8_t*) current_huff_node->item, file_out);
				current_huff_node = huff_root;
			}
			
			bool go_right = is_bit_i_set(current_file_byte, i);
			current_huff_node = go_right ? current_huff_node->right_child
										 : current_huff_node->left_child;
		}
	}
	
	for (uint8_t i = 0; i < (8 - trash_size); i++) { /** < Lê o último byte. */
		fscanf(file_in, "%c", &current_file_byte);
		if (CHECK_IS_CONTROL(current_huff_node)) {
			fputc(*(uint8_t*) current_huff_node->left_child->item, file_out);
			current_huff_node = huff_root;
		} else if (current_huff_node->left_child == NULL && current_huff_node->right_child == NULL) {
			fputc(*(uint8_t*) current_huff_node->item, file_out);
			current_huff_node = huff_root;
		}
		
		current_huff_node = is_bit_i_set(current_file_byte, i) ? current_huff_node->right_child
															   : current_huff_node->left_child;
	}
	
	fclose(file_in);
	fclose(file_out);
	
	printf("\n\n"
		   "Descodificacao completa! Digite 0 para continuar.\n"
		   "\n");
	scanf("%d", &cr);
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
	*(uint8_t*) new_node->item = pre_order_str[current_index];
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