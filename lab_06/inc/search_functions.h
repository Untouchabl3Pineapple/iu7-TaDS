#ifndef __SEARCH_FUNCTIONS_H__

#define __SEARCH_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"
#include "constants.h"
#include "hash_get_val.h"

uint64_t tick(void);

int file_search(FILE *tree_file, const int val);

tnode_t *tree_traversal(tnode_t *root, const int val, int *cmpc, int *eflag);

int tree_search(tnode_t *root, const int val, char *const tname, FILE *tree_file);

int hash_table_search(lnode_t **hash_table, const int key, const int val, int cmpc, const int size);

#endif // __SEARCH_FUNCTIONS_H__
