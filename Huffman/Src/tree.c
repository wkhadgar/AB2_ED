#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"

huff_t* create_huff_tree(priority_queue_t* priority_queue){
    
    
    
    huff_t* huff1; 
    huff_t* huff2;
    huff_t* father;
    
    

    /*Soma das frequências dos dois nós desenfileirados.*/
    uint64_t freqsum;

    while (priority_queue->size > 0){
        
        /*Desenfileira os dois nós com menos frequência.*/
        huff1 = dequeue(priority_queue);
        huff2 = dequeue(priority_queue);
        
        /*Soma a frequência dos dois nós desenfileirados.*/
        freqsum = huff1->freq + huff2->freq;
        
        /*Asterisco para criar o pai.*/
        unsigned char item = 42;
        
        //printf("Criando um pai para os bytes: %X e %X\n",*(unsigned char*)huff1->item,*(unsigned char*)huff2->item);
        
        /*Se a árvore estiver vazia, cria um pai para os últimos dois nós e retorna essa pai como raiz da árvore.*/
        if(priority_queue->size == 0){
            
            return create_huff_node(&item,freqsum,huff1,huff2);
        }
        
        if((*(unsigned char*)huff2->item == '*' && *(unsigned char*)huff1->item != '*') && (huff1->freq == huff2->freq)){
			
            father = create_huff_node(&item,freqsum,huff2,huff1);
            enqueue(priority_queue,father);
    
		}
        else{
            
            father = create_huff_node(&item,freqsum,huff1,huff2);
            enqueue(priority_queue,father);
        }

            /*Debugging da arvore.*/
            /*printf("Essa e a fila depois das operacoes:\n");
            print_queue(priority_queue);
            printf("\n");*/
    }
    return father;
    
}

void print_preorder(huff_t* root){

    if(!is_tree_empty(root)){
        if(*(unsigned char*)root->item == 42)
            printf("%c ",*(unsigned char*)root->item);
        else
            printf("%X ",*(unsigned char*)root->item);
        //if(root->down_left == NULL && root->down_right == NULL)
        //printf("%c ",*(unsigned char*)root->item);
        print_preorder(root->down_left);
        print_preorder(root->down_right);
    } 

}

bool is_tree_empty(huff_t* root){
    return root == NULL;
}

int tree_size(huff_t* root){
	if(root == NULL) return 0;
	else return  1 + tree_size(root -> down_left) + tree_size(root -> down_right);
}