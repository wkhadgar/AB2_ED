
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
    uint64_t freq;
    struct huff* down_left;
    struct huff* down_right;
} huff_t;

/**
 * @brief Struct do nó da fila de prioridade.
 */
typedef struct node {
    huff_t* value;
    struct node* next;
} node_t;

/**
 * @brief Struct da fila de prioridade. A struct consiste em um ponteiro para a cabeça da fila.
 */
typedef struct priority_queue {
    node_t* head;
} priority_queue_t;

#endif /** HUFF_DEFINES_H */
