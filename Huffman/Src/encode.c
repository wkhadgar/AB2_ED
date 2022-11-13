#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"
#include <math.h>

void compress() {
	
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
	int cr;
	int input;
	scanf("%s", file_in_name);
	file_in = fopen(file_in_name, "rb");
	
	if (file_in == NULL) {
		printf("Nome de arquivo inválido, ou o arquivo não foi encontrado. O que fazer?\n"
			   "[1] - Tentar comprimir novamente...\n"
			   "[2] - Retornar para o menu.\n"
			   "-> ");
		
		scanf("%d", &input);
		if (input == 1) {
			compress();
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
		printf("This is the priority queue.");
		print_queue(priority_queue);
		printf("\n\n");
		/*Teste da função dequeue.*/
		/*node_t*node = dequeue(priority_queue);
		printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);
		node = dequeue(priority_queue);
		printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);*/
		
	}
	
	/*Debugging da árvore.*/
	huff_t* tree = create_huff_tree(priority_queue);
	{
		print_preorder(tree);
		//print_queue(priority_queue);
		printf("\n The tree has a size of: %d\n", tree_size(tree));
	}
	
	create_coding(tree, ht, 0, 0, 0, 0);
	print_coding(ht);
	
	int bits = total_bits(ht);
	int totalbytes = total_bytes(bits);
	
	printf("The compressed/encoded file_in will have %d bits and %d bytes.\n\n", bits, totalbytes);
	
	int treesize = tree_size(tree);
	int trash = (totalbytes * 8) - bits;
	
	printf("The trash has %d bits .\n", trash);
	
	printf("\nInsert the compressed/encoded file_in name without it's extension:\n-> ");
	scanf("%s", file_out_name);
	
	strcat(file_out_name, ".zap");
	
	printf("\n");
	file_out = fopen(file_out_name, "wb");
	
	print_header(trash, treesize, file_out, tree);//Imprime o header no novo arquivo codificado.
	
	file_in = fopen(file_in_name, "rb");
	
	int nbits, newbytesize = 0;
	
	
	unsigned char writebyte, c, aux = 0;
	int control, empty_bits = 8;
	
	while (fscanf(file_in, "%c", &current_char) != EOF) {
		
		control = ht->table[current_char]->new_byte_size;
		empty_bits = empty_bits - control;
		c = ht->table[current_char]->new_byte;
		if (empty_bits <= 0) {
			aux = aux | (c >> abs(empty_bits));
			print_byte(aux);
			fputc(aux, file_out);
			empty_bits = 8 + empty_bits;
			aux = 0;
			while (empty_bits < 0) {
				aux |= (c >> abs(empty_bits));
				fputc(aux, file_out);
				print_byte(aux);
				empty_bits = 8 + empty_bits;
				aux = 0;
			}
			aux |= (c << empty_bits);
		} else aux |= (c << empty_bits);
		
		
	}
	if (trash != 0)fputc(aux, file_out);
	print_byte(aux);
	fclose(file_out);
	fclose(file_in);
	
	fflush(stdin);
	printf("\nCompression/Encoding done!\nPress 0 to continue.\n\n");
	scanf("%d", &cr);
	
	return;
}

void create_coding(huff_t* root, hash_t* ht, int shift_bit, unsigned int newbyte, int byte, int flag) {
	if (root == NULL)
		return;
	
	if (flag) {
		newbyte = newbyte | byte;//Adiciona o bit no novo byte. Sempre adiciona no lsb.
		newbyte = newbyte << 1;//Abre espaço para o próximo bit ser adicionado.
	}
	
	
	if (root->left_child == NULL && root->right_child == NULL) {//Se achar uma folha, coloca o item na hash.
		put(ht, root->item, shift_bit, newbyte, root->freq);
	}
	create_coding(root->left_child, ht, shift_bit + 1, newbyte, 0, 1);
	create_coding(root->right_child, ht, shift_bit + 1, newbyte, 1, 1);
	
}

void print_coding(hash_t* ht) {
	for (int i = 0; i < BYTE_RANGE; i++) {
		if (ht->table[i] != NULL) {
			printf("The byte %c new representation has ", *(unsigned char*) ht->table[i]->byte);
			print_bits(ht->table[i]);
			printf("\n");
		}
		
	}
	
}

void print_bits(table_t* table) {
	int g = 1;
	unsigned char b;
	b = table->new_byte;
	printf("%d bits, it's int equals to %d and the new bits are:", table->new_byte_size, table->new_byte);
	for (int i = table->new_byte_size - 1; i >= 0; i--) {
		
		b = table->new_byte >> i;
		//printf("%d",i);
		if (g & b)
			printf("1");
		else
			printf("0");
		//a = a>>1;
		b = table->new_byte;
		
	}
	
}

int total_bits(hash_t* ht) {
	int bits = 0;
	int i;
	for (i = 0; i < BYTE_RANGE; i++)
		if (ht->table[i] != NULL)
			bits += (ht->table[i]->new_byte_size * ht->table[i]->freq);
	
	return bits;
}

int total_bytes(double bits) {
	return ceil(bits / 8);
}

void print_header(int trash, int treesize, FILE* fout, huff_t* tree) {
	
	unsigned char bytes[2];
	bytes[0] = trash << 5 | treesize
			>> 8; //Coloca o lixo nas três primeiras posições. e coloca os 5 primeiros bits do tamanho da arvore nas últimas 5.
	bytes[1] = treesize;  //Coloca o restante do tamanho da árvore no segundo byte.                        
	
	fputc(bytes[0], fout);//O fputc converte o byte para unsigned char antes de printar no arquivo.
	fputc(bytes[1], fout);
	
	//fprintf(fout,"%d",bytes);
	
	
	print_tree_file(tree, fout);
}

void print_tree_file(huff_t* tree, FILE* fout) {
	if (tree != NULL) {
		if (tree->freq != 0) {
			if (((*(unsigned char*) tree->item == 92) || *(unsigned char*) tree->item == 42) &&
				(tree->left_child == NULL && tree->right_child == NULL))
				fputc(92, fout);
			fputc(*(int*) tree->item, fout);
			print_tree_file(tree->left_child, fout);
			print_tree_file(tree->right_child, fout);
		}
	}
}

int print_byte(int a) {
	
	int g = 1;
	unsigned char b;
	b = a;
	for (int i = 7; i >= 0; i--) {
		
		b = a >> i;
		//printf("%d",i);
		if (g & b)
			printf("1");
		else
			printf("0");
		//a = a>>1;
		b = a;
		
	}
	printf("\n");
}

int is_bit_i_set(unsigned char c, int i) {
	unsigned char mask = 1 << i;
	return mask & c;
}

unsigned char set_bit(unsigned char c, int i) {
	unsigned char mask = 1 << i;
	return mask | c;
}