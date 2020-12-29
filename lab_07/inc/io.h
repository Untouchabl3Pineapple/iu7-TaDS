#ifndef __IO_H__

#define __IO_H__

#include <stdio.h>

#include "constants.h"
#include "data_structures.h"
#include "memory_functions.h"
#include "process.h"

int matrix_fill(graph_t *graph, FILE *file);

void matrix_print(graph_t graph);

int graph_vis(graph_t graph);

#endif // __IO_H__
