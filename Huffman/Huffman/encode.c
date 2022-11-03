#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "structs.h"
#include "queue.h"
void presentation()
{
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
void menu()
{
    int input;
    system("cls");
    presentation();
    printf("Welcome to the huffman encoder version 2.0\n1 - Compress a file\n2 - Decompress a file\n0 - Exit\n");
    while (input != 0)
    {
        
        
        scanf("%d",&input);
        if (input == 1)
        compress();
        
     
    }
}
void compress()
{
    char s[100];
    unsigned char freq[255] = {0}; 
    unsigned char c;
    FILE*file;
    system("cls");
    presentation();
    printf("Type the file's name with it's correct extension:\n");
    char cr;
    scanf("%s",s);
    file = fopen(s,"rb");
    if (file == NULL)
        {
            printf("Num deu\n");
            return;
        }
    while (fscanf(file, "%c",&c) != EOF) 
		freq[c]++;
    fclose(file);
    PQueue *fila;//cria um ponteiro para a cabeça da fila
    for (int i = 0;i<256;i++)
        {
            
            if(freq[i]!= 0)
                {
                    //enqueue(fila,i,freq[i]);
                    //printf("O byte %d aparece %d vezes\n",i,freq[i]);
                }
            
        }
    
    printf("Do you wish to continue?\n Y/N");
    scanf("%c",&cr);
}