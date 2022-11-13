#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "huff_defines.h"

/**
 * @brief Inicializa a fila de prioridade.
 * @return Retorna o endereço da alocação.
 */
priority_queue_t*create_priority_queue();

/**
 * @brief Diz se a fila está vazia ou não.
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 * @return Retorna true se a fila estiver vazia, e false se não estiver.
 */
bool is_empty(priority_queue_t* priority_queue);

/**
 * @brief Enfileira em ordem crescente.
 *
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 * @param new_huff Nó de huffman a ser enfileirado.
 */
void enqueue(priority_queue_t* priority_queue,huff_t* new_huff);

/**
 * @brief Desenfileira o nó da cabeça.
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 * @return Retorna NULL se a fila estiver vazia ou o nó que estava na cabeça
 */
huff_t* dequeue(priority_queue_t *priority_queue);

/**
 * @brief Imprime na tela todos os elementos da fila.
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 */

void print_queue(priority_queue_t* priority_queue);

/**
 * @brief Cria um nó de huffman.
 * @param item Valor a ser armazenado pelo nó.
 * @param freq Frequência que esse valor aparece no arquivo.
 * @param left_child Filho a esquerda do nó.
 * @param right_child Filho a direita do nó.
 * @return Retorna um ponteiro para a alocação de um nó.
 */
huff_t* create_huff_node(void* item, uint64_t freq, huff_t* left_child, huff_t* right_child, bool is_before_tree);