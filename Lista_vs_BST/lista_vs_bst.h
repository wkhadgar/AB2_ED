#ifndef AB2_ED_LISTA_VS_BST_H
#define AB2_ED_LISTA_VS_BST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

/**
 * @brief Define se o número de reruns será usado como tamanho da pool se verdadeiro, ou se o tamanho da pool será fixo caso falso.
 */
#define DYN_SIZE_RUN 1

/**
 * @brief Número de repetições para a pesquisa na estrutura.
 */
#define RERUNS 500

#if DYN_SIZE_RUN == 0
/**
 * @brief Tamanho da pool de pesquisa, para reruns fixos.
 */
#define POOL_SIZE_MAX 2000
#endif

/**
 * @brief Estrutura da lista.
 */
typedef struct list {
#if DYN_SIZE_RUN
	int values[RERUNS];
#else
	int values[POOL_SIZE_MAX];
#endif
} list_t;

/**
 * @brief Estrutura da árvore de busca binária.
 */
typedef struct BT {
	int val;
	struct BT* left;
	struct BT* right;
} binary_tree_t;


/**
 * @brief Preenche a lista com valores aleatórios.
 *
 * @param l [in,out] Ponteiro para a cabeça da lista.
 * @param size Tamanho da lista.
 */
void fill_list(list_t* l, int size);

/**
 * @brief Gera um novo nó na árvore, mantendo a propriedade de uma BST.
 *
 * @param root [in,out] Raiz da árvore.
 * @param n Valor do nó.
 */
void add_bst_node(binary_tree_t* root, int n);

/**
 * @brief Realiza a busca na lista.
 *
 * @param l [in,out] Ponteiro para a cabeça da lista.
 * @param size Tamanho da lista.
 * @param n Valor a ser pesquisado.
 * @return int Número de pesquisas para achar o valor, negativo se não encontrado.
 */
int search_list(list_t* l, int size, int n);

/**
 * @brief Realiza a busca na BST.
 *
 * @param bst [in] Raiz da BST.
 * @param n Valor a ser pesquisado.
 * @param steps Quantos passos foram dados. Deve ser chamado inicialmente com 0.
 * @return int Número de pesquisas para achar o valor, negativo se não encontrado.
 */
int search_tree(binary_tree_t* bst, int n, int steps);


void print_list(list_t* l, int size);

void print_tree(binary_tree_t* root, int level);

#endif //AB2_ED_LISTA_VS_BST_H