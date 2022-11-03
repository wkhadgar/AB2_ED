#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

void enqueue(PQueue *pq, void* i, int p);
int is_empty(PQueue*pq);