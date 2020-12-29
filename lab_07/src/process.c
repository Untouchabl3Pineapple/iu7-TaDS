#include "../inc/process.h"

void paths_fill(graph_t graph)
{
    int min_len[graph.size];
    int mark_vert[graph.size];
    int minind, min;

    for (int begin_ind = 0; begin_ind < graph.size; begin_ind++)
    {
        for (int i = 0; i < graph.size; i++)
        {
            min_len[i] = INT_MAX;
            mark_vert[i] = 1;
        }

        min_len[begin_ind] = 0;

        do
        {
            minind = INT_MAX;
            min = INT_MAX;

            for (int i = 0; i < graph.size; i++)
            {
                if (mark_vert[i] == 1 && min_len[i] < min)
                {
                    min = min_len[i];
                    minind = i;
                }
            }

            if (minind != INT_MAX)
            {
                for (int i = 0, temp; i < graph.size; i++)
                {
                    if (graph.matrix[minind][i] > 0)
                    {
                        temp = min + graph.matrix[minind][i];

                        if (temp < min_len[i])
                            min_len[i] = temp;
                    }
                }

                mark_vert[minind] = 0;
            }

        } while (minind < INT_MAX);

        for (int i = 0; i < graph.size; i++)
        {
            graph.paths[begin_ind][i] = min_len[i];
        }
    } 
}

int get_min_path(graph_t graph)
{
    int min = INT_MAX, ind = 0;

    for (int i = 0, sum; i < graph.size; i++)
    {
        sum = 0;

        for (int j = 0; j < graph.size; j++)
        {
            sum += graph.paths[i][j];
        }

        if (sum < min)
        {
            min = sum;
            ind = i;
        }
    }

    return ind;
}

