#ifndef __MEMORY_FUNCTIONS_H__

#define __MEMORY_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "data_structures.h"

int allocate_graph(graph_t *graph);

void free_graph(graph_t *graph);

#endif // __MEMORY_FUNCTIONS_H__
