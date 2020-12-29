#ifndef __ADDITIONAL_FUNCTIONS_H__

#define __ADDITIONAL_FUNCTIONS_H__

#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/io.h"
#include "../inc/main_functions.h"

#include <stdlib.h>

int array_stack_copy(array_stack_t *stack, array_stack_t *stack_copy, array_stack_t *stack_temp);

int list_stack_copy(number_t **head, number_t **head_copy, number_t **head_temp);

size_t array_stack_counter_el(array_stack_t *stack, const int element);

size_t list_stack_counter_el(number_t *head, const int element);

int array_stack_max_el(array_stack_t *stack, array_stack_t *sorted_stack);

int list_stack_max_el(number_t **head, number_t **sorted_head);

size_t list_stack_size(number_t *head);

void list_stack_free(number_t **head);

#endif // __ADDITIONAL_FUNCTIONS_H__
