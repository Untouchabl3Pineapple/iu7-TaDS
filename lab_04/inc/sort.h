#ifndef __SORT_H__

#define __SORT_H__

#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/io.h"
#include "../inc/additional_functions.h"

#include <stdlib.h>

int array_stack_sort(array_stack_t *stack_1, \
array_stack_t *stack_2, array_stack_t *stack_res);

int list_stack_sort(number_t **head_1, \
number_t **head_2, number_t **head_res);

#endif // __SORT_H__
