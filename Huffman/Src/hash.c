#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"

void put(hash_t* ht, void*item, int shift_bit, unsigned short int newbyte,uint64_t freq){

    int g = *(int*)item % BYTE_RANGE;
    ht->table[g] = (table_t*)malloc(sizeof(table_t));
    ht->table[g]->byte = item;
    ht->table[g]->new_byte = newbyte >> 1;
    ht->table[g]->new_byte_size = shift_bit;
    ht->table[g]->freq = freq;



}
hash_t* create_hash_table(){
    hash_t* new_ht = (hash_t*)malloc(sizeof(hash_t));
    for (int i = 0; i < BYTE_RANGE; i++){
        new_ht->table[i] = NULL;
    }
    return new_ht;
    
}