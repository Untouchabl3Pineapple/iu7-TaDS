#ifndef __MEMORY_FUNCTIONS_H__

#define __MEMORY_FUNCTIONS_H__

#include <stdlib.h>

#include "data_structures.h"
#include "constants.h"

int vector_init(vector_q *vector);

node_t *list_element_init(const int val);

void lfree(node_t *tail);

#endif // __MEMORY_FUNCTIONS_H__
