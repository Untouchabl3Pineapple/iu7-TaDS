#ifndef __PROCESS_H__

#define __PROCESS_H__

#include <stdio.h>
#include <limits.h>

#include "constants.h"
#include "data_structures.h"

void paths_fill(graph_t graph);

int get_min_path(graph_t graph);

#endif // __PROCESS_H__
