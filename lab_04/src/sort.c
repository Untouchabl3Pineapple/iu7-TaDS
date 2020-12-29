#include "../inc/sort.h"

int array_stack_sort(array_stack_t *stack_1, \
array_stack_t *stack_2, array_stack_t *stack_res)
{
    array_stack_t stack_res_copy, temp_stack;

    if (array_stack_init(&stack_res_copy) != OK)
        return MEMORY_ALLOCATION_ERROR;
    if (array_stack_init(&temp_stack) != OK)
    {
        free(stack_res_copy.data);
        return MEMORY_ALLOCATION_ERROR;
    }

    if (array_stack_copy(stack_1, &stack_res_copy, &temp_stack) != OK)
        return STACK_OVERFLOW;
    if (array_stack_copy(stack_2, &stack_res_copy, &temp_stack) != OK)
        return STACK_OVERFLOW;

    for (int i = 0; i < stack_res_copy.top; i++)
    {
        for (; array_stack_empty(&stack_res_copy) == OK;)
        {
            if (array_stack_push(stack_res, array_stack_max_el(&stack_res_copy, stack_res)) != OK)
            {
                free(stack_res_copy.data);
                free(temp_stack.data);
                return STACK_OVERFLOW;
            }
        }
        array_stack_copy(stack_1, &stack_res_copy, &temp_stack);
        array_stack_copy(stack_2, &stack_res_copy, &temp_stack);
    }

    free(stack_res_copy.data);
    free(temp_stack.data);

    return OK;
}

int list_stack_sort(number_t **head_1, \
number_t **head_2, number_t **head_res)
{
    int stack_size;
    number_t *head_res_copy, *head_temp;

    *head_res = NULL;
    head_res_copy = NULL;
    head_temp = NULL;

    list_stack_copy(head_1, &head_res_copy, &head_temp);
    list_stack_copy(head_2, &head_res_copy, &head_temp);

    stack_size = list_stack_size(head_res_copy);

    for (int i = 0; i < stack_size; i++)
    {
        for (; list_stack_empty(head_res_copy) == OK;)
        {
            if (list_stack_push(head_res, list_stack_max_el(&head_res_copy, head_res)) != OK)
            {
                list_stack_free(&head_res_copy);
                list_stack_free(&head_temp);
                return STACK_OVERFLOW;
            }
        }
        list_stack_copy(head_1, &head_res_copy, &head_temp);
        list_stack_copy(head_2, &head_res_copy, &head_temp);
    }

    list_stack_free(&head_res_copy);
    list_stack_free(&head_temp);

    return OK;
}
