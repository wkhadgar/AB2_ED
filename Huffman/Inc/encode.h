#include <stdint.h>
#include "huff_defines.h"

/**
 * @brief Imprime na tela uma arte em caracteres ascii.
 */
void presentation();

/**
 * @brief Comprime/Codifica o arquivo.
 */
void encode();

/**
 * @brief Entry point para a criação da hash.
 *
 * @param root Ponteiro para a raiz da ávore de huffman.
 * @param ht Ponteiro para a hash table.
 */
void create_endoded_ht(huff_t* root, hash_t* ht);

/**
 * @brief Imprime na tela a nova codificação dos bytes.
 *
 * @param ht Ponteiro para a hash table.
 */
void print_coding(hash_t* ht);

/**
 * @brief Imprime na tela os bits da nova codificação.
 *
 * @param table Ponteiro para o nó da hash table.
 */
void print_bits(table_t* table);

/**
 * @brief Calcula o total de bits do novo arquivo codificado.
 * 
 * @param ht Ponteiro para a hash table que contém as frequencias e a nova codificação dos bytes.
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

void print_byte(uint8_t byte);

void print_header(uint8_t trash, uint16_t treesize, FILE* fout, huff_t* tree);

void fprint_tree_bytes(huff_t* root, FILE* fout);