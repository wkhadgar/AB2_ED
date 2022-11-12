#include "huff_defines.h"

void put(hash_t* ht, void*item, int shift_bit, unsigned short int newbyte, uint64_t freq);

/**
 * @brief inicializa a hash table.
 *
 * @return Retorna um ponteiro para a nova hash table.
 */
hash_t* create_hash_table();