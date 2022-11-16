
#ifndef AB2_ED_DECODE_H
#define AB2_ED_DECODE_H

#include "huff_defines.h"
#include "tree.h"

/**
 * @brief Entry point da decodificação.
 *
 * @return function_retval_t Qual opção de erro a ser tomada.
 */
function_retval_t decode(void);

/**
 * @brief Monta uma árvore de huffman a partir de uma string em pré-ordem.
 *
 * @param pre_order_str string a ser montada.
 * @return huff_t* [out] Ponteiro para a raiz da árvore de huffman.
 */
huff_t* create_huff_tree_from_str(const uint8_t* pre_order_str);

#endif //AB2_ED_DECODE_H