#ifndef __HASH_GET_VAL_H__

#define __HASH_GET_VAL_H__

#include "data_structures.h"
#include "constants.h"

#define MAIN_KEY (abs(val) % 10 + 1)
#define SPARE_KEY (abs(val) % 100 + 1)

int hash_get_val(lnode_t **table, const int key, const int val, \
                int cmpc, int *counter, const int pflag);

#endif // __HASH_GET_VAL_H__
