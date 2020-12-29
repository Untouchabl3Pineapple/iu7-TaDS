#ifndef __DATA_STRUCTURES_H__

#define __DATA_STRUCTURES_H__

#include <stdio.h>

#include "constants.h"

typedef struct
{
    int *data;

    size_t top;
    size_t size;  

} array_stack_t;

// FOR LIST
typedef struct number_t
{
    int data;

    struct number_t *next;

} number_t;

typedef struct
{
    number_t *free_array_points[MAX_LEN_ARRAY_FREE];

    int len;

} free_points_t;

free_points_t array; 

#endif // __DATA_STRUCTURES_H__
