#ifndef __DATA_STRUCTURES_H__

#define __DATA_STRUCTURES_H__

#include <stdio.h>

#include "constants.h"

typedef struct
{
    int *data;
    /*
    *   first element point
    *   second element point
    */
    size_t felp, lelp;
} vector_q;

typedef struct node_t
{
    int data;

    struct node_t *next;
} node_t;

typedef struct
{
    node_t *free_array_points[MAX_LEN_ARRAY_FREE];

    int len;
} free_points_t;

free_points_t array;

#endif // __DATA_STRUCTURES_H__
