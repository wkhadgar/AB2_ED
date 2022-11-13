#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "queue.h"
#include "huff_defines.h"

int menu(void); /** UI do projeto */

int main() {
	
	//presentation();
	while (menu()){}
	
    printf("The real huffman encoding are the friends we made along the way.\n\n\n\n\n");
}

int menu(void) {
	int32_t input = -1;
	
	while (input != 0) {
		
		printf("Bem-vindo ao codificador de Huffman v2.0, escolha uma das opções a seguir.\n"
			   "[1] - Comprimir um arquivo.\n"
			   "[2] - Descomprimir um arquivo codificado.\n"
			   "[0] - Sair.\n"
			   "-> ");
		
		scanf("%d", &input);
		if (input == 1) {
			compress();
		} else if (input == 0) {
			return 0;
		} else if (input == 2) {
		} else {
			return -2;
		}
		
		return -1;
	}
}


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