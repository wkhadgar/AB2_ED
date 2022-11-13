
#ifndef HUFF_DEFINES_H
#define HUFF_DEFINES_H

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
	uint8_t new_byte; /** < Nova representação do byte */
	uint8_t new_byte_size; /** < Quantos bits a nova representação tem */
} table_t;

typedef struct hash {
	table_t* table[BYTE_RANGE];
} hash_t;


#endif /** HUFF_DEFINES_H */