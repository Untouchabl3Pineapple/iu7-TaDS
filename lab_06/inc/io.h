#ifndef __IO_H__

#define __IO_H__

#include <string.h>
#include <stdlib.h>

#include "data_structures.h"
#include "constants.h"
#include "memory_functions.h"
#include "balance.h"

#define MAIN_KEY (abs(val) % 10 + 1)
#define SPARE_KEY (abs(val) % 100 + 1)

tnode_t *add_tdnode(tnode_t *droot, const int val, int *h);

tnode_t *add_tavlnode(tnode_t *avlroot, const int val, int *h);

int bin_tree_filling(tnode_t **droot, tnode_t **avlroot, FILE *tree_file);

void tree_print(tnode_t *root, int space);

int hash_table_fill(lnode_t **hash_table, FILE *tree_file, int *max_ind, \
                    char *const filter);

void hash_table_print(lnode_t **table, const int max_ind);

#endif // __IO_H__
