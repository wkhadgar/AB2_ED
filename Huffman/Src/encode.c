#include <string.h>
#include "encode.h"
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"
#include <math.h>

/**
 * @brief Cria a nova codificação dos bytes.
 *
 * @param root Ponteiro para a raiz da ávore de huffman.
 * @param ht Ponteiro para a hash table.
 * @param shift_bit Quantidade de bits da nova codificação.
 * @param newbyte Variável para guardar os bits da codificação.
 * @param bit bit a ser adicionado a nova representação.
 */
static void create_encoding(huff_t* root, hash_t* ht, uint32_t shift_bit, uint32_t newbyte, uint8_t bit);

void encode() {
	
	uint8_t file_in_name[MAX_FILE_NAME_SIZE];
	uint8_t file_out_name[MAX_FILE_NAME_SIZE];
	
	uint64_t frequencies_map[BYTE_RANGE] = {0}; /** < Mapeia a frequência dos bytes no arquivo. */
	uint8_t current_char;
	
	FILE* file_in;
	FILE* file_out;
	
	priority_queue_t* priority_queue = create_priority_queue();
	
	hash_t* ht = create_hash_table();
	
	/** Enfeite visual */
	{
		//presentation();
		printf("Type the file_in's name with it's correct extension:\n-> ");
	}
	
	/** Leitura do arquivo */
	uint32_t cr;
	uint32_t input;
	scanf("%s", file_in_name);
	file_in = fopen(file_in_name, "rb");
	
	if (file_in == NULL) {
		printf("Nome de arquivo inválido, ou o arquivo não foi encontrado. O que fazer?\n"
			   "[1] - Tentar comprimir novamente...\n"
			   "[2] - Retornar para o menu.\n"
			   "-> ");
		
		scanf("%d", &input);
		if (input == 1) {
			encode();
			return;
		} else if (input == 2) {
			return;
		}
	}
	
	/**
	 * Montagem do mapa de frequências com as frequências.
	 *
	 * @note Cada índice do array representa um byte, e está sendo usado como chave da hash.
	 */
	while (fscanf(file_in, "%c", &current_char) != EOF) {
		frequencies_map[current_char] += 1;
	}
	fclose(file_in);
	
	/** Montagem da fila de prioridades */
	uint8_t byte_value = 0;
	do {
		if (frequencies_map[byte_value] != 0) {
			huff_t* huff = create_huff_node(&byte_value, frequencies_map[byte_value], NULL, NULL, true);
			enqueue(priority_queue, huff);
			//printf("O byte %X aparece %llu vezes\n", byte_value, frequencies_map[byte_value]);
		}
		byte_value++;
	} while (byte_value != 0); /** Quando o byte der overflow, para.*/
	
	
	/*Os comandos abaixo são apena para testar a fila.*/
	{
		/*Teste do enqueue.*/
		printf("A fila de prioridades ficou assim: ");
		print_queue(priority_queue);
		printf("\n\n");
		/*Teste da função dequeue.*/
		/*node_t*node = dequeue(priority_queue);
		printf("\nThe dequeued item is: %X\n",*(uint8_t
		 *)node->value->item);
		node = dequeue(priority_queue);
		printf("\nThe dequeued item is: %X\n",*(uint8_t
		 *)node->value->item);*/
		
	}
	
	/*Debugging da árvore.*/
	huff_t* tree = create_huff_tree(priority_queue);
	{
		print_preorder(tree);
		//print_queue(priority_queue);
		printf("\n"
			   " A arvore tem tamanho %d.\n", tree_size(tree));
	}
	
	create_endoded_ht(tree, ht);
	print_coding(ht);
	
	uint64_t num_bits = total_bits(ht);
	uint64_t num_bytes = total_bytes((double) num_bits);
	
	printf("O arquivo codificado tem %llu bytes (%llu bits).\n"
		   "\n", num_bytes, num_bits);
	
	uint32_t treeSize = tree_size(tree);
	uint32_t trash = 8 - (num_bits % 8); /**< 8 é o tamanho de um byte */
	
	printf("O tamanho do lixo é %d bits.\n", trash);
	
	printf("\n"
		   "Insira o nome do arquivo compactado:\n"
		   "-> ");
	scanf("%s", file_out_name);
	
	strcat(file_out_name, ".zap2");
	
	printf("\n");
	file_out = fopen(file_out_name, "wb");
	
	/** Imprime o header no novo arquivo codificado. */
	print_header(trash, treeSize, file_out, tree);
	
	file_in = fopen(file_in_name, "rb"); /**< Reabre o arquivo para poder transcrever com a hash */
	
	uint8_t new_byte_size, new_byte, aux = 0;
	int8_t empty_bits = 8;
	
	while (fscanf(file_in, "%c", &current_char) != EOF) {
		
		new_byte_size = ht->table[current_char]->new_byte_size;
		new_byte = ht->table[current_char]->new_byte;
		
		empty_bits = (int8_t) (empty_bits - new_byte_size);
		
		if (empty_bits <= 0) { /** Quando tamanho do new_byte for maior ou igual a 8 */
			aux = aux | (new_byte >> abs(empty_bits)); /** Seleciona apenas o primeiro byte do new_byte */
			fputc(aux, file_out); /* E coloca ele no arquivo */
			empty_bits = (int8_t) (8 + empty_bits); /* Vemos o que falta */
			aux = 0;
			while (empty_bits < 0) { /* Repete até ficar ok */
				aux = aux | (new_byte >> abs(empty_bits));
				fputc(aux, file_out);
				empty_bits = 8 + empty_bits;
				aux = 0;
			}
			aux = aux | (new_byte << empty_bits);
		} else {
			aux = aux | (new_byte << empty_bits);
		}
	}
	
	if (trash != 0) {
		fputc(aux, file_out);
	}
	
	fclose(file_out);
	fclose(file_in);
	
	printf("\n"
		   "Codificação completa!\n"
		   "Digite 0 para continuar.\n"
		   "\n");
	scanf("%u", &cr);
}

static void create_encoding(huff_t* root, hash_t* ht, uint32_t shift_bit, uint32_t newbyte, uint8_t bit) {
	if (root == NULL)
		return;
	
	newbyte = newbyte | bit; /**< Adiciona o bit no novo bit. Sempre adiciona no lsb.*/
	newbyte = newbyte << 1; /**< Abre espaço para o próximo bit ser adicionado. */
	
	if (CHECK_IS_CONTROL(root)) { /** Se é um nó de controle (que por consequência, é uma "folha") */
		put(ht, root->left_child->item, shift_bit, newbyte, *(uint64_t*) root->left_child->freq);
	} else if ((root->left_child == NULL && root->right_child == NULL)) {
		/** Senão, se for uma folha, coloca o item na hash. */
		put(ht, root->item, shift_bit, newbyte, *(uint64_t*) root->freq);
	}
	
	if (!CHECK_IS_CONTROL(root)) {
		create_encoding(root->left_child, ht, shift_bit + 1, newbyte, 0);
	}
	create_encoding(root->right_child, ht, shift_bit + 1, newbyte, 1);
}

void create_endoded_ht(huff_t* root, hash_t* ht) {
	create_encoding(root, ht, 0, 0, 0);
}

void print_coding(hash_t* ht) {
	for (uint32_t i = 0; i < BYTE_RANGE; i++) {
		if (ht->table[i] != NULL) {
			printf("The byte %c new representation has ", *(uint8_t*) ht->table[i]->byte);
			print_bits(ht->table[i]);
			printf("\n");
		}
		
	}
	
}

void print_bits(table_t* table) {
	uint16_t new_byte;
	new_byte = table->new_byte;
	printf("%d bits, it's uint32_t equals to %d and the new bits are:", table->new_byte_size, new_byte);
	
	for (int16_t i = table->new_byte_size - 1; i >= 0; i--) {
		
		new_byte = table->new_byte >> i;
		
		if (new_byte & 1) {
			printf("1");
		} else {
			printf("0");
		}
	}
}

uint64_t total_bits(hash_t* ht) {
	uint64_t num_bits = 0;
	uint16_t i;
	
	for (i = 0; i < BYTE_RANGE; i++)
		if (ht->table[i] != NULL) {
			num_bits += (ht->table[i]->new_byte_size * ht->table[i]->freq);
		}
	
	return num_bits;
}

uint64_t total_bytes(double bits) {
	return ceil(bits / 8.0);
}

void print_header(uint8_t trash, uint16_t treesize, FILE* fout, huff_t* tree) {
	
	uint8_t header_first_bytes[2];
	/** Coloca o lixo nas três primeiras posições, depois coloca os 5 primeiros bits do tamanho da arvore nas últimas 5. */
	header_first_bytes[0] = trash << 5 | treesize >> 8;
	
	/** Coloca o restante do tamanho da árvore no segundo byte. */
	header_first_bytes[1] = treesize;
	
	fputc(header_first_bytes[0], fout);//O fputc converte o byte para uint8_t antes de printar no arquivo.
	fputc(header_first_bytes[1], fout);
	
	fprint_tree_bytes(tree, fout);
}

void fprint_tree_bytes(huff_t* root, FILE* fout) {
	if (root != NULL) {
		if (CHECK_IS_CONTROL(root)) {
			fputc('\\', fout);
			fputc(*(uint8_t*) root->left_child->item, fout);
		} else {
			fputc(*(uint8_t*) root->item, fout);
		}
		
		if (!CHECK_IS_CONTROL(root)) {
			fprint_tree_bytes(root->left_child, fout);
		}
		fprint_tree_bytes(root->right_child, fout);
	}
}

void print_byte(uint8_t byte) {
	
	uint8_t b;
	
	for (int8_t i = 7; i >= 0; i--) {
		
		b = byte >> i;
		if (b & 1) {
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");
}

bool is_bit_i_set(uint8_t byte, uint8_t i) {
	uint8_t mask = 128 >> i;
	return mask & byte;
}

uint8_t set_bit(uint8_t byte, uint8_t i) {
	uint8_t mask = 128 >> i;
	return mask | byte;
}