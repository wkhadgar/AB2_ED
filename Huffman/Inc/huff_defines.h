
#ifndef HUFF_DEFINES_H
#define HUFF_DEFINES_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

/**
 * @brief define para trocar a forma de interpretar o tamanho da arvore como tamanho da string ou da arvore
 */
//#define TREE_TRUE_SIZE

/**
 * @brief Valor máximo de um byte.
 */
#define BYTE_MAX_VALUE 255

/**
 * @brief Quantidade de valores diferentes que um byte pode assumir.
 */
#define BYTE_RANGE 256

/**
* @brief Tamanho máximo do nome do arquivo
*/
#define MAX_FILE_NAME_SIZE 100

/**
 * @brief Checa se o nó dado é de controle (\) ou não.
 */
#define CHECK_IS_CONTROL(x) (*(uint8_t*) (x)->item == '\\')

/**
 * @brief enum das saídas das funções.
 */
typedef enum {
	ENCODE_REPEAT = 0,
	ENCODE_CANCEL,
	DECODE_REPEAT,
	DECODE_CANCEL,
	NONE_SELECTED
} function_retval_t;

/**
 * @brief Struct da codificação de huffman
 */
typedef struct huff {
	void* item;
	void* freq;
	struct huff* next;
	struct huff* left_child;
	struct huff* right_child;
} huff_t;

/**
 * @brief Struct da fila de prioridade. A struct consiste em um ponteiro para a cabeça da fila, e um inteiro representando o seu tamanho.
 */
typedef struct priority_queue {
	uint8_t size;
	void* head;
} priority_queue_t;

/**
 * @brief Struct que armazena os dados de um byte de Huffman.
 */
typedef struct table {
	void* byte;
	uint64_t freq;
	uint16_t new_byte; /** < Nova representação do byte */
	uint8_t new_byte_size; /** < Quantos bits a nova representação tem */
} table_t;

/**
 * @brief Estrutura da hash de Huffman.
 */
typedef struct hash {
	table_t* table[BYTE_RANGE];
} hash_t;

/**
 * @brief Cria um nó de huffman.
 * @param item Valor a ser armazenado pelo nó.
 * @param freq Frequência que esse valor aparece no arquivo.
 * @param left_child Filho a esquerda do nó.
 * @param right_child Filho a direita do nó.
 * @param is_before_tree cria o nó de controle se verdadeiro, se não, apenas cria um nó.
 * @return Retorna um ponteiro para a alocação de um nó.
 */
huff_t* create_huff_node(void* item, uint64_t freq, huff_t* left_child, huff_t* right_child, bool is_before_tree);

/**
 * @brief Verifica se um bit está setado dentro do byte.
 *
 * @param byte Byte a ser checado.
 * @param i Índice, da esquerda para direita, do bit a ser verificado.
 * @return bool falso se o bit não está setado, verdadeiro caso contrário.
 */
bool is_bit_i_set(uint8_t byte, uint8_t i);

/**
 * @brief Imprime na tela uma arte em caracteres ascii.
 */
void presentation();

#endif /** HUFF_DEFINES_H */