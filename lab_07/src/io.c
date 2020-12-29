#include "../inc/io.h"

int matrix_fill(graph_t *graph, FILE *file)
{        
    if (fscanf(file, "%d", &graph->size) != 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (graph->size < 1)
        return MATRIX_FILL_PARAMETR_ERROR;

    if (allocate_graph(graph) != OK)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            if (fscanf(file, "%d", &graph->matrix[i][j]) != 1)
                return MATRIX_FILL_ELEMENT_ERROR;

            if (graph->matrix[i][j] < 0)
                return MATRIX_FILL_ELEMENT_ERROR;
        }
    }

    return OK;
}

void matrix_print(graph_t graph)
{
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            printf("%10d ", graph.matrix[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

int graph_vis(graph_t graph)
{
    FILE *filemain, *filepaths;
    int min_row = get_min_path(graph);

    filemain = fopen("road_system.dot", "w");
    if (filemain == NULL)
        return FILE_OPEN_ERROR;

    filepaths = fopen("paths.dot", "w");
    if (filepaths == NULL)
        return FILE_OPEN_ERROR;

    fprintf(filemain, "graph Roadsystem {\n");
    fprintf(filepaths, "graph paths {\n");

    char cityname = 'A';

    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
        {
            if (graph.matrix[i][j] != 0 && i >= j) 
                fprintf(filemain, "%c -- %c [label=%d];\n", cityname + i, cityname + j, graph.matrix[i][j]);
        }
    }

    for (int i = 0; i < graph.size; i++)
    {
        if (graph.paths[min_row][i] != 0)
            fprintf(filepaths, "%c -- %c [label=%d];\n", cityname + min_row, cityname + i, graph.paths[min_row][i]);
    }

    fprintf(filemain, "}\n");
    fprintf(filepaths, "}\n");

    fclose(filemain);
    fclose(filepaths);

    system("dot -Tpng road_system.dot -o main_graph.png");
    system("dot -Tpng paths.dot -o paths_graph.png");

    system("open main_graph.png");
    system("open paths_graph.png");

    return OK;
}
