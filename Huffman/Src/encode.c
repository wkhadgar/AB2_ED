#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"
#include <math.h>

void presentation() {
    system("cls");
    printf("      ___           ___           ___         ___         ___           ___           ___         \n");
    printf("     /__/\\         /__/\\         /  /\\       /  /\\       /__/\\         /  /\\         /__/\\        \n");
    printf("     \\  \\:\\        \\  \\:\\       /  /:/_     /  /:/_     |  |::\\       /  /::\\        \\  \\:\\       \n");
    printf("      \\__\\:\\        \\  \\:\\     /  /:/ /\\   /  /:/ /\\    |  |:|:\\     /  /:/\\:\\        \\  \\:\\      \n");
    printf("  ___ /  /::\\   ___  \\  \\:\\   /  /:/ /:/  /  /:/ /:/  __|__|:|\\:\\   /  /:/~/::\\   _____\\__\\:\\     \n");
    printf(" /__/\\  /:/\\:\\ /__/\\  \\__\\:\\ /__/:/ /:/  /__/:/ /:/  /__/::::| \\:\\ /__/:/ /:/\\:\\ /__/::::::::\\    \n");
    printf(" \\  \\:\\/:/__\\/ \\  \\:\\ /  /:/ \\  \\:\\/:/   \\  \\:\\/:/   \\  \\:\\~~\\__\\/ \\  \\:\\/:/__\\/ \\  \\:\\~~\\~~\\/    \n");
    printf("  \\  \\::/       \\  \\:\\  /:/   \\  \\::/     \\  \\::/     \\  \\:\\        \\  \\::/       \\  \\:\\  ~~~     \n");
    printf("   \\  \\:\\        \\  \\:\\/:/     \\  \\:\\      \\  \\:\\      \\  \\:\\        \\  \\:\\        \\  \\:\\         \n");
    printf("    \\  \\:\\        \\  \\::/       \\  \\:\\      \\  \\:\\      \\  \\:\\        \\  \\:\\        \\  \\:\\        \n");
    printf("     \\__\\/         \\__\\/         \\__\\/       \\__\\/       \\__\\/         \\__\\/         \\__\\/        \n");
    printf("      ___           ___           ___           ___          _____          ___           ___     \n");
    printf("     /  /\\         /__/\\         /  /\\         /  /\\        /  /::\\        /  /\\         /  /\\    \n");
    printf("    /  /:/_        \\  \\:\\       /  /:/        /  /::\\      /  /:/\\:\\      /  /:/_       /  /::\\   \n");
    printf("   /  /:/ /\\        \\  \\:\\     /  /:/        /  /:/\\:\\    /  /:/  \\:\\    /  /:/ /\\     /  /:/\\:\\  \n");
    printf("  /  /:/ /:/_   _____\\__\\:\\   /  /:/  ___   /  /:/  \\:\\  /__/:/ \\__\\:|  /  /:/ /:/_   /  /:/~/:/  \n");
    printf(" /__/:/ /:/ /\\ /__/::::::::\\ /__/:/  /  /\\ /__/:/ \\__\\:\\ \\  \\:\\ /  /:/ /__/:/ /:/ /\\ /__/:/ /:/___\n");
    printf(" \\  \\:\\/:/ /:/ \\  \\:\\~~\\~~\\/ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/  \\  \\:\\  /:/  \\  \\:\\/:/ /:/ \\  \\:\\/:::::/\n");
    printf("  \\  \\::/ /:/   \\  \\:\\  ~~~   \\  \\:\\  /:/   \\  \\:\\  /:/    \\  \\:\\/:/    \\  \\::/ /:/   \\  \\::/~~~~ \n");
    printf("   \\  \\:\\/:/     \\  \\:\\        \\  \\:\\/:/     \\  \\:\\/:/      \\  \\::/      \\  \\:\\/:/     \\  \\:\\     \n");
    printf("    \\  \\::/       \\  \\:\\        \\  \\::/       \\  \\::/        \\__\\/        \\  \\::/       \\  \\:\\    \n");
    printf("     \\__\\/         \\__\\/         \\__\\/         \\__\\/                       \\__\\/         \\__\\/    \n");
}

void menu() {
    int input = -1;

    
    while (input != 0) {

        presentation();
        printf("Welcome to the huffman encoder version 2.0\n1 - Compress a file\n2 - Decompress a file\n0 - Exit\n-> ");

        scanf("%d", &input);
        if (input == 1){
            compress();
        }
        else if (input == 0){
            return;
        }
        
    }
}

void compress() {

    int8_t file_name[MAX_FILE_NAME_SIZE];
    int8_t file_name2[MAX_FILE_NAME_SIZE];

    uint64_t frequencies_hash[BYTE_RANGE] = {0};
    uint8_t bytes[BYTE_RANGE];
    uint8_t current_char;

    FILE* file;
    FILE* fout;

    priority_queue_t* priority_queue = create_priority_queue();

    hash_t* ht = create_hash_table();

    /** Enfeite visual */
    {
        presentation();
        printf("Type the file's name with it's correct extension:\n-> ");
    }

    /** Leitura do arquivo */
    int cr;
    int input;
    scanf("%s", file_name);
    file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Invalid filename, missing file or some other shit.\n1 - Compress/encode again\nPress 2 - Return to menu.\n-> ");
        scanf("%d",&input);
        if(input == 1){
                compress();
                return;
            }
        else if(input == 2){
                //menu();
                return;
            }
    }

    /**
     * @brief  Montagem da hash table com as frequências.
     *
     * @note Cada índice do array representa um byte, e está sendo usado como chave da hash.
     */
    while (fscanf(file, "%c", &current_char) != EOF) {
        frequencies_hash[current_char] += 1;
    }
    fclose(file);

    /** Montagem da fila de prioridades */
    for (int i = 0; i < BYTE_RANGE; i++) {

        if (frequencies_hash[i] != 0) {
            huff_t* huff = create_huff_node(&i,frequencies_hash[i],NULL,NULL);
            enqueue(priority_queue, huff);
            //printf("O byte %X aparece %llu vezes\n", i, frequencies_hash[i]);
        }
    }
    /*Os comandos abaixo são apena para testar a fila.*/
    {
        /*Teste do enqueue.*/
        printf("This is the priority queue.");
        print_queue(priority_queue);
        printf("\n\n");
        /*Teste da função dequeue.*/
        /*node_t*node = dequeue(priority_queue);
        printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);
        node = dequeue(priority_queue);
        printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);*/

    }
    /*Debugging da árvore.*/
    huff_t* tree = create_huff_tree(priority_queue);
    {
        
        print_preorder(tree);
        //print_queue(priority_queue);
        printf("\n The tree has a size of: %d\n",tree_size(tree));
    }

    create_coding(tree,ht,0,0,0,0);
    print_coding(ht);
    
    int bits = total_bits(ht);
    int totalbytes = total_bytes(bits);
    
    printf("The compressed/encoded file will have %d bits and %d bytes.\n\n",bits,totalbytes);

    int treesize = tree_size(tree);
    int trash = (totalbytes*8) - bits;
    
    printf("The trash has %d bits .\n",trash);

    printf("\nInsert the compressed/encoded file name without it's extension:\n-> ");
	scanf("%s", file_name2);
	
    strcat(file_name2,".zap");
    
    printf("\n");
	fout = fopen(file_name2, "wb");

    print_header(trash,treesize,fout,tree);//Imprime o header no novo arquivo codificado.

    file = fopen(file_name,"rb");
    
    int nbits,newbytesize = 0;
    
    
    unsigned char writebyte , c, aux = 0;
    int control ,empty_bits = 8;
    
    while (fscanf(file, "%c", &current_char) != EOF) {
        
        control = ht->table[current_char] -> shift_bit;
		empty_bits = empty_bits - control;
		c = ht->table[current_char] ->newbyte;
		if(empty_bits <= 0)
		{
			aux = aux | (c >> abs(empty_bits));
			print_byte(aux);
            fputc(aux, fout);
			empty_bits =  8 + empty_bits;
			aux = 0;
			while(empty_bits < 0)
			{
				aux |= (c >> abs(empty_bits));
				fputc(aux, fout);
                print_byte(aux);
				empty_bits =  8 + empty_bits;
				aux = 0;
			}
			aux |= (c << empty_bits);
		}
		else aux |= (c << empty_bits);


        
    }
    if(trash != 0)fputc(aux, fout);
    print_byte(aux);
    fclose(fout);
    fclose(file);

    fflush(stdin);
    printf("\nCompression/Encoding done!\nPress 0 to continue.\n\n");
    scanf("%d", &cr);
    
    return;
}

void create_coding(huff_t* root, hash_t* ht, int shift_bit, unsigned int newbyte, int byte, int flag){
    if(root == NULL)
        return;
    
    if(flag)
    {
        newbyte = newbyte | byte;//Adiciona o bit no novo byte. Sempre adiciona no lsb.
        newbyte = newbyte << 1;//Abre espaço para o próximo bit ser adicionado.
    }

    
    if(root->down_left == NULL && root->down_right == NULL){//Se achar uma folha, coloca o item na hash.
        put(ht,root->item,shift_bit,newbyte,root->freq);
    }
    create_coding(root->down_left,ht,shift_bit+1,newbyte,0,1);
    create_coding(root->down_right,ht,shift_bit+1,newbyte,1,1);

}
void print_coding(hash_t* ht){
    for (int i = 0; i < BYTE_RANGE; i++)
    {
        if(ht->table[i]!= NULL)
        {
            printf("The byte %c new representation has ",*(unsigned char*)ht->table[i]->byte);
            print_bits(ht->table[i]);
            printf("\n");
        }
        
    }
    
}
void print_bits(table_t* table){
    int g = 1;
    unsigned char b;
    b = table->newbyte;
    printf("%d bits, it's int equals to %d and the new bits are:",table->shift_bit,table->newbyte);
    for(int i = table->shift_bit-1;i>=0;i--)
        {
           
            b = table->newbyte>>i;
            //printf("%d",i);
            if (g & b)
             printf("1");
            else
                printf("0");
            //a = a>>1;
           b = table->newbyte; 
           
        }

}

int total_bits(hash_t* ht){
    int bits = 0;
	int i;
	for(i = 0; i < BYTE_RANGE; i++)
	    if(ht->table[i] != NULL) 
	    	bits += (ht->table[i]->shift_bit * ht->table[i]->freq);

	    return bits;
}

int total_bytes(double bits){
    return ceil(bits/8);
}

void print_header(int trash,int treesize,FILE* fout,huff_t* tree){

    unsigned char bytes [2];
	bytes[0] = trash << 5 | treesize >> 8; //Coloca o lixo nas três primeiras posições. e coloca os 5 primeiros bits do tamanho da arvore nas últimas 5. 
	bytes[1] = treesize;  //Coloca o restante do tamanho da árvore no segundo byte.                        

	fputc(bytes[0], fout);//O fputc converte o byte para unsigned char antes de printar no arquivo.
	fputc(bytes[1], fout);                         

	//fprintf(fout,"%d",bytes);
    
	
	print_tree_file(tree, fout);
}
void print_tree_file(huff_t* tree, FILE* fout)
{
    if(tree != NULL)
	{
		if(tree->freq != 0)
		{
			if(((*(unsigned char*)tree->item == 92) || *(unsigned char*)tree->item == 42) && (tree->down_left == NULL && tree->down_right == NULL)) fputc(92, fout);
			fputc(*(int*)tree->item, fout);
			print_tree_file(tree->down_left, fout);
			print_tree_file(tree->down_right, fout);
		}
	}
}
int print_byte(int a)
{
    
    int g = 1;
    unsigned char b;
     b=a; 
     for(int i = 7;i>=0;i--)
        {
           
            b = a>>i;
            //printf("%d",i);
            if (g&b)
             printf("1");
            else
                printf("0");
            //a = a>>1;
           b=a; 
           
        }
    printf("\n");
}
int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}
unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}