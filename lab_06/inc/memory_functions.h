#ifndef __MEMORY_FUNCTIONS_H__

#define __MEMORY_FUNCTIONS_H__

#include <stdlib.h>
#include <limits.h>

#include "data_structures.h"
#include "constants.h"

tnode_t *tree_node_init(const int val, const int h);

lnode_t **hash_table_init(lnode_t **hash_table);

lnode_t *list_element_init(const int val);

#endif // __MEMORY_FUNCTIONS_H__
