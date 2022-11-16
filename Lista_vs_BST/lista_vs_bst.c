#include "lista_vs_bst.h"

int main() {
	
	int32_t data[RERUNS][3]; /**< Tabela de dados, [nº reruns x (pesquisas)] */
	
	srand(time(NULL)); /**< Seed pra gerar os nums aleatórios */
	
	printf("Se os passos estiverem negativos, entao nao foi achado o valor.\n");
	
	for (int32_t turn = 1; turn <= RERUNS; turn++) {
		
		int chosen_num;
		list_t lista;
		binary_tree_t bst;

#if DYN_SIZE_RUN
		chosen_num = rand() % turn;
		fill_list(&lista, turn);
#else
		chosen_num = rand() % POOL_SIZE_MAX;
		fill_list(&lista, POOL_SIZE_MAX);
#endif
		//printf("\n----------------------\nchoosen: %d\n", chosen_num);
		
		/** Cria a raiz da árvore, baseado na lista */
		bst.val = lista.values[0];
		bst.left = NULL;
		bst.right = NULL;

#if DYN_SIZE_RUN
		for (int i = 1; i < turn; i++)  {
				add_bst_node(&bst, lista.values[i]);
			}

			int bst_results = search_tree(&bst, chosen_num, 0);
			int lista_results = search_list(&lista, turn, chosen_num);
			data[turn-1][2] = turn; /** Tamanho da pool atual */
#else
		for (int i = 1; i < POOL_SIZE_MAX; i++) {
			add_bst_node(&bst, lista.values[i]);
		}
		
		int bst_results = search_tree(&bst, chosen_num, 0);
		int lista_results = search_list(&lista, POOL_SIZE_MAX, chosen_num);
		data[turn - 1][2] = POOL_SIZE_MAX; /** Tamanho da pool atual */
#endif
		
		/** Preenche os dados na tabela */
		data[turn - 1][0] = bst_results;
		data[turn - 1][1] = lista_results;
		
		// descomentar caso queira verificar os resultados na mão
		//print_list(&lista, DYN_SIZE_RUN?turn:POOL_
		//SIZE_MAX);
		//print_tree(&bst, 1);
		
		//printf("\nbusca na BST: %d steps\nbusca na lista: %d steps\n", bst_results, lista_results);
	}
	
	FILE* fp;
#if DYN_SIZE_RUN
	fp = fopen("./results/dynamic_pool.csv", "w+");
#else
	fp = fopen("./results/fixed_pool.csv", "w+");
#endif
	
	fprintf(fp, "bst,lista,search_pool_size\n");
	for (int i = 0; i < RERUNS; i++) {
		//("turn %d - bst:%d, lista:%d\n", i + 1, data[i][0], data[i][1]);
		fprintf(fp, "%d,%d,%d\n", data[i][0], data[i][1], data[i][2]);
	}
	fclose(fp);
	
	return 0;
}

void fill_list(list_t* l, int size) {
	for (int i = 0; i < size; i++) {
		l->values[i] = rand() % size;
		//printf("%dst choosen: %d\n", i+1, rand()); //mostra os sorteados pra formar a lista
	}
}

void print_list(list_t* l, int size) {
	
	printf("lista:\n[ ");
	for (int i = 0; i < size; i++) {
		printf("%d - ", l->values[i]);
	}
	printf("\b\b]\n");
}

void print_tree(binary_tree_t* root, int level) {
	if (!root) {
		return;
	}
	for (int i = 0; i < level - 1; i++) {
		printf(i != 0 ? "|   " : "    ");
	}
	
	printf("|--{%d\n", root->val);
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}

void add_bst_node(binary_tree_t* root, int n) {
	binary_tree_t* new_node = (binary_tree_t*) malloc(sizeof(binary_tree_t));
	new_node->val = n;
	new_node->left = NULL;
	new_node->right = NULL;
	
	int is_left = 0; //decide qual lado vai jogar o node
	binary_tree_t* previous_node;
	while (root != NULL) { //ate chegar no fim de um node
		previous_node = root; // lembra o ultimo node caminhado
		if (root->val >= new_node->val) { //o valor do node atual é maior que do novo
			root = root->left; //vai pra esquerda
			is_left = 1;
		} else { //direita
			root = root->right;
			is_left = 0;
		}
		
	}
	if (is_left) previous_node->left = new_node; //se for pra esquerda no final, coloca o novo node lá
	else previous_node->right = new_node;
}

int search_list(list_t* l, int size, int n) {
	int i = 0;
	for (; i < size; i++) {
		if (l->values[i] == n) return i + 1;  /**< Achou e retorna o número de passos */
	}
	return -i; /**< Não achou, retorna o negativo dos passos */
}

int search_tree(binary_tree_t* bst, int n, int steps) {
	if (bst == NULL) {
		return -(steps + 1); /**< Esgotou a busca sem achar. */
	} else if (bst->val == n) {
		return steps + 1; //achou aqui
	} else if (n > bst->val) {
		return search_tree(bst->right, n, steps + 1); //num é maior, vai pra direita
	} else {
		return search_tree(bst->left, n, steps + 1); //num é menor ou igual, vai pra esquerda
	}
}