//Struct da codificação de huffman
typedef struct huff Huff;
struct huff
{
	void *item;
	int freq;
	struct huff *down_left;
	struct huff *down_right;
};
//Struct do nó da fila de prioridade.
typedef struct  node Node;
struct node 
{
    Huff* item;
    Node *next;
};
//Struct da fila de prioridade. A struct consiste em um ponteiro para a cabeça da fila.
typedef struct priority_queue PQueue;
struct priority_queue 
{
    Node *head;
};
