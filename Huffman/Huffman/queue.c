#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
int is_empty(PQueue*pq)
{
    return pq == NULL;
}
void enqueue(PQueue *pq, void* i, int p)
{
    Huff* new_huff = (Huff*) malloc(sizeof(Huff));
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_huff->down_left = NULL;
    new_huff->down_right = NULL;
    new_node->item->item = i;
    new_node->item = new_huff;
    new_node->item->freq = p;
    if ((is_empty(pq)) || (p > pq->head->item->freq)) 
    {
        new_node->next = pq->head;
        pq->head = new_node;
    } 
    else 
    {
        Node *current = pq->head;
        while ((current->next != NULL) &&(current->next->item->freq > p))
            current = current->next;
    
        new_node->next = current->next;
        current->next = new_node;
    }
}