#include <stdint.h>
#include "huff_defines.h"

/**
 * @brief Imprime na tela uma arte em caracteres ascii.
 */
void presentation();

/**
 * @brief Comprime/Codifica o arquivo.
 */
void compress();

/**
 * @brief Interface visual.
 */
void menu();

/**
 * @brief Cria a nova codificação dos bytes.
 * 
 * @param root Ponteiro para a raiz da ávore de huffman.
 * @param ht Ponteiro para a hash table.
 * @param shift_bit Quantidade de bits da nova codificação.
 * @param newbyte Variável para guardar os bits da codificação.
 * @param byte bit a ser adicionado a nova representação.
 */
void create_coding(huff_t* root, hash_t* ht, int shift_bit, unsigned int newbyte,int byte,int flag);

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
 * 
 * @return Retorna o a quantidade total de bits do arquivo codificado.
*/
int total_bits(hash_t* ht);

/**
 * @brief Calcula o total de bytes do novo arquivo codificado.
 * 
 * @param bits Quantidade total de bits do aquivo codificado.
 * 
 * @return Retorna a quantidade de bytes do novo arquivo.
*/
int total_bytes(double bits);

int print_byte(int a);

void print_header(int trash,int treesize,FILE* fout,huff_t* tree);
void print_tree_file(huff_t* tree, FILE* fout);


int is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);