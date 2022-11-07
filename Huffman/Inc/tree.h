#include "huff_defines.h"
#include "queue.h"

/**
 * @brief Cria a árvore de huffman. 
 * 
 * @param priority_queue Ponteiro para a fila de prioridade.
 * 
 * @return Retorna um nó que é a raiz da árvore.
*/
huff_t* create_huff_tree(priority_queue_t* priority_queue);

/**
 * @brief Imprime a árvore em pré-ordem. 
 * 
 * @param root Ponteiro para a raiz da árvore.
 */
void print_preorder(huff_t* root);

/**
 * @brief Diz se a árvore está vazia ou não. 
 * 
 * @param root Ponteiro para a raiz da árvore.
 * 
 * @return Retorna true se a árvore está vazia, ou false se ela não estiver.
 */
bool is_tree_empty(huff_t* root);

/**
 * @brief Calcula o tamanho da árvore. 
 * 
 * @param root Ponteiro para a raiz da árvore.
 * 
 * @return Retorna o tamanho da árvore.
 */
int tree_size(huff_t* root);