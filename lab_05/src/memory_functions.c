#include "../inc/memory_functions.h"

int vector_init(vector_q *vector)
{
    // VECTOR_SIZE = __
    vector->data = (int *)malloc(QUEUE_SIZE * sizeof(int));

    if (vector == NULL)
        return MEMORY_ALLOCATION_ERROR;

    vector->felp = 1;
    vector->lelp = 0;

    return OK;
}

node_t *list_element_init(const int val)
{   
    node_t *node = (node_t *)malloc(sizeof(struct node_t));

    if (node)
    {
        (node)->data = val;
        (node)->next = NULL; 
    }

    return node;
}

void lfree(node_t *tail)
{
    node_t *next;

    for (; tail; tail = next)
    {
        next = tail->next;
        free(tail);
    }
}

