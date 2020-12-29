#ifndef __IO_H__

#define __IO_H__

#include <stdio.h>
#include <stdlib.h>

#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/main_functions.h"
#include "../inc/additional_functions.h"

int array_stack_init(array_stack_t *stack);

number_t *list_element_init(const int value);

int stack_fill(array_stack_t *stack, number_t **head);

void array_stack_print(array_stack_t *stack);

void list_stack_print(number_t **head);

void info(void);

void menu(void);

void print_error(const int exit_code);

#endif // __IO_H__
