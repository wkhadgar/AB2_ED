#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "encode.h"
#include "huff_defines.h"
#include "queue.h"
#include "tree.h"

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
    int input;

    presentation();
    printf("Welcome to the huffman encoder version 2.0\n1 - Compress a file\n2 - Decompress a file\n0 - Exit\n");
    while (input != 0) {

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

    uint64_t frequencies_hash[BYTE_RANGE] = {0};
    uint8_t bytes[BYTE_RANGE];
    uint8_t current_char;

    FILE* file;

    priority_queue_t* priority_queue = create_priority_queue();

    /** Enfeite visual */
    {
        presentation();
        printf("Type the file's name with it's correct extension:\n");
    }

    /** Leitura do arquivo */
    char cr;
    scanf("%s", file_name);
    file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Num deu\n");
        return;
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
            printf("O byte %X aparece %llu vezes\n", i, frequencies_hash[i]);
        }
    }
    /*Os comandos abaixo são apena para testar a fila.*/
    {
        /*Teste do enqueue.*/
        print_queue(priority_queue);
        printf("\n\n");
        /*Teste da função dequeue.*/
        /*node_t*node = dequeue(priority_queue);
        printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);
        node = dequeue(priority_queue);
        printf("\nThe dequeued item is: %X\n",*(unsigned char*)node->value->item);*/

    }
    /*Debugging da árvore.*/
    {
        huff_t*tree = create_huff_tree(priority_queue);
        print_preorder(tree);
        //print_queue(priority_queue);
        printf("\n The tree has a size of: %d\n",tree_size(tree));
    }

    printf("\nDo you wish to decode/decompress the file?\n Y/N\n\n");
    scanf("%c", &cr);
    if (cr == 'n')
        return;
}