#ifndef __LIST_QUEUE_H__

#define __LIST_QUEUE_H__

#include "data_structures.h"
#include "constants.h"
#include "memory_functions.h"

int lpush(node_t **tail, const int val);

int lpop(node_t **tail);

int lpeek(node_t *tail);

int lempty(node_t *tail);

int lsize(node_t *tail);

int lcopy(node_t **tail, node_t **tail_copy, node_t **tail_temp);

#endif // __LIST_QUEUE_H__
