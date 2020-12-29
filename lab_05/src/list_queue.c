#include "../inc/list_queue.h"

int lpush(node_t **tail, const int val)
{
    if (tail == NULL)
        return NULL_POINTER;

    node_t *node = list_element_init(val);
    if (node == NULL)
        return MEMORY_ALLOCATION_ERROR;

    node->next = *tail;
    *tail = node;

    return OK;
}

int lpop(node_t **tail) 
{
    if (tail == NULL)
        return NULL_POINTER;

    if (lempty(*tail) == QUEUE_EMPTY) 
        return QUEUE_UNDERFLOW;

    int tail_value;
    node_t* temp_node;

    temp_node = *tail;
    tail_value = temp_node->data;
    *tail = (*tail)->next;

    free(temp_node);

    return tail_value;
}

int lpeek(node_t *tail)
{
    if (tail == NULL)
        return NULL_POINTER;

    if (lempty(tail) == QUEUE_EMPTY) 
        return QUEUE_UNDERFLOW;

    return tail->data;
}

int lempty(node_t *tail)
{
    if (tail == NULL)
        return QUEUE_EMPTY;

    return OK;
}

int lsize(node_t *tail)
{
    int counter = 0;

    for (; tail; tail = tail->next)
    {
        counter++;
    }

    return counter;
}

int lcopy(node_t **tail, node_t **tail_copy, node_t **tail_temp)
{
    *tail_copy = NULL;
    *tail_temp = NULL;

    for (; lempty(*tail) == OK; lpop(tail))
    {
        if (lpush(tail_temp, lpeek(*tail)) != OK)
            return QUEUE_OVERFLOW;
    }

    for (; lempty(*tail_temp) == OK; lpop(tail_temp))
    {
        if (lpush(tail, lpeek(*tail_temp)) != OK)
            return QUEUE_OVERFLOW;
        if (lpush(tail_copy, lpeek(*tail_temp)) != OK)
            return QUEUE_OVERFLOW;
    }

    return OK;
}
