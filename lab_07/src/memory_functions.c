#include "../inc/memory_functions.h"

int allocate_graph(graph_t *graph)
{
    graph->matrix = (int **) calloc(graph->size, sizeof(int*));
    if (!graph->matrix)
        return MEMORY_ALLOCATION_ERROR;

    graph->paths = (int **) calloc(graph->size, sizeof(int*));
    if (!graph->paths)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < graph->size; i++)
    {
        graph->matrix[i] = (int *) calloc(graph->size, sizeof(int));
        if (!graph->matrix[i])
            return MEMORY_ALLOCATION_ERROR;

        graph->paths[i] = (int *) calloc(graph->size, sizeof(int));
        if (!graph->paths[i])
            return MEMORY_ALLOCATION_ERROR;
    }

    return OK;
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        free(graph->matrix[i]);
    }

    for (int i = 0; i < graph->size; i++)
    {
        free(graph->paths[i]);
    }

    free(graph->matrix);
    free(graph->paths);
}
