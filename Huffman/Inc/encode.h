#include <stdint.h>
#include "huff_defines.h"

/**
 * @brief Entry point da codificacao do arquivo.
 *
 * @return function_retval_t Qual opção de erro a ser tomada.
 */
function_retval_t encode();

/**
 * @brief Entry point para a criação da hash.
 *
 * @param root [in] Ponteiro para a raiz da ávore de huffman.
 * @param ht [out] Ponteiro para a hash table.
 */
void create_endoded_ht(huff_t* root, hash_t* ht);

/**
 * @brief Imprime na tela a nova codificação dos bytes.
 *
 * @param ht [in] Ponteiro para a hash table.
 */
void print_coding(hash_t* ht);

/**
 * @brief Imprime na tela os bits da nova codificação.
 *
 * @param table [in] Ponteiro para o nó da hash table.
 */
void print_bits(table_t* table);

/**
 * @brief Calcula o total de bits do novo arquivo codificado.
 * 
 * @param ht [in] Ponteiro para a hash table que contém as frequencias e a nova codificação dos bytes.
 * @return Retorna o a quantidade total de bits do arquivo codificado.
*/
uint64_t total_bits(hash_t* ht);

/**
 * @brief Calcula o total de bytes do novo arquivo codificado.
 * 
 * @param bits Quantidade total de bits do aquivo codificado.
 * @return Retorna a quantidade de bytes do novo arquivo.
*/
uint64_t total_bytes(double bits);

/**
 * @brief Imprime o header do arquivo comprimido.
 *
 * @param trash Tamanho do lixo.
 * @param treesize Tamanho da arvore.
 * @param fout [out] Arquivo a ser escrito.
 * @param tree [in] Raiz da árvore de Huffman montada.
 *
 * @note O tamanho da árvore é aqui o tamanho da string em pós ordem,
 * caso TREE_TRUE_SIZE não esteja definido.
 */
void print_header(uint8_t trash, uint16_t treesize, FILE* fout, huff_t* tree);

/**
 * @brief Imprime a árvore em pré ordem no arquivo.
 *
 * @param root Raiz da árvore de Huffman montada.
 * @param fout [out] Arquivo a ser escrito.
 */
void fprint_tree_bytes(huff_t* root, FILE* fout);