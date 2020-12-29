#ifndef __MAIN_FUNCTIONS_H__

#define __MAIN_FUNCTIONS_H__

#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/io.h"

int array_stack_push(array_stack_t *stack, const int value);

int list_stack_push(number_t **head, const int value);

int array_stack_pop(array_stack_t *stack);

int list_stack_pop(number_t **head);

int array_stack_peek(array_stack_t *stack);

int list_stack_peek(number_t *head);

int array_stack_empty(array_stack_t *stack);

int list_stack_empty(number_t *head);

#endif // __MAIN_FUNCTIONS_H__
