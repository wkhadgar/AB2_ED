#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "huff_defines.h"

/**
 * @brief Enfileira em ordem crescente.
 *
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 * @param item Valor a ser ranqueado pela fila.
 * @param freq Prioridade do valor associado.
 */
void enqueue(priority_queue_t* priority_queue, void* item, uint64_t freq);

/**
 * @brief Diz se a fila está vazia ou não.
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 * @return Retorna true se a fila estiver vazia, e false se não estiver.
 */
bool is_empty(priority_queue_t* priority_queue);

/**
 * @brief Imprime na tela todos os elementos da fila.
 * @param priority_queue [in] Ponteiro para a fila de prioridades.
 */
void print_queue(priority_queue_t* priority_queue);