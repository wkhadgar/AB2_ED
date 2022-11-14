#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"

void put(hash_t* ht, void* item, uint8_t shift_bit, uint16_t new_byte, uint64_t freq) {
	
	uint8_t key = *(uint8_t*) item;
	ht->table[key] = (table_t*) malloc(sizeof(table_t));
	ht->table[key]->byte = item;
	ht->table[key]->new_byte = new_byte >> 1; /** Elimina o shift antes do put */
	ht->table[key]->new_byte_size = shift_bit;
	ht->table[key]->freq = freq;
}

hash_t* create_hash_table() {
	hash_t* new_ht = (hash_t*) malloc(sizeof(hash_t));
	for (int i = 0; i < BYTE_RANGE; i++) {
		new_ht->table[i] = NULL;
	}
	return new_ht;
	
}