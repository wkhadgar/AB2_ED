
#ifndef AB2_ED_DECODE_H
#define AB2_ED_DECODE_H

#include "huff_defines.h"
#include "tree.h"

void decode(void);

huff_t* create_huff_tree_from_str(const uint8_t* pre_order_str);

#endif //AB2_ED_DECODE_H