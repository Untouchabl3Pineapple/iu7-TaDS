#include "../inc/additional_functions.h"

int array_stack_copy(array_stack_t *stack, array_stack_t *stack_copy, array_stack_t *stack_temp)
{
    for (; array_stack_empty(stack) == OK; array_stack_pop(stack))
    {
        if (array_stack_push(stack_temp, array_stack_peek(stack)) != OK)
            return STACK_OVERFLOW;
    }
    for (; array_stack_empty(stack_temp) == OK; array_stack_pop(stack_temp))
    {
        if (array_stack_push(stack, array_stack_peek(stack_temp)) != OK)
            return STACK_OVERFLOW;
        if (array_stack_push(stack_copy, array_stack_peek(stack_temp)) != OK)
            return STACK_OVERFLOW;
    }

    return OK;
}

int list_stack_copy(number_t **head, number_t **head_copy, number_t **head_temp)
{
    for (; list_stack_empty(*head) == OK; list_stack_pop(head))
    {
        if (list_stack_push(head_temp, list_stack_peek(*head)) != OK)
            return STACK_OVERFLOW;
    }
    for (; list_stack_empty(*head_temp) == OK; list_stack_pop(head_temp))
    {
        if (list_stack_push(head, list_stack_peek(*head_temp)) != OK)
            return STACK_OVERFLOW;
        if (list_stack_push(head_copy, list_stack_peek(*head_temp)) != OK)
            return STACK_OVERFLOW;
    }

    return OK;
}

size_t array_stack_counter_el(array_stack_t *stack, const int element)
{
    array_stack_t stack_copy, stack_temp;
    size_t counter = 0;

    if (array_stack_init(&stack_copy) != OK)
        return MEMORY_ALLOCATION_ERROR;
    if (array_stack_init(&stack_temp) != OK)
    {
        free(stack_copy.data);
        return MEMORY_ALLOCATION_ERROR;
    }

    array_stack_copy(stack, &stack_copy, &stack_temp);

    for (; array_stack_empty(&stack_copy) == OK;)
    {
        if (array_stack_pop(&stack_copy) == element)
            counter++;
    }

    free(stack_copy.data);
    free(stack_temp.data);

    return counter;
}

size_t list_stack_counter_el(number_t *head, const int element)
{
    number_t *head_copy, *head_temp;
    size_t counter = 0;

    head_copy = NULL;
    head_temp = NULL;

    list_stack_copy(&head, &head_copy, &head_temp);

    for (; list_stack_empty(head_copy) == OK;)
    {
        if (list_stack_pop(&head_copy) == element)
            counter++;
    }

    list_stack_free(&head_copy);
    list_stack_free(&head_temp);

    return counter;
}

int array_stack_max_el(array_stack_t *stack, array_stack_t *sorted_stack)
{
    if (array_stack_empty(stack) != OK)
        return STACK_EMPTY;

    int max = array_stack_peek(stack);
    for (; array_stack_counter_el(stack, max) <= array_stack_counter_el(sorted_stack, max);)
    {
        array_stack_pop(stack);
        max = array_stack_peek(stack);
    }

    for (int temp_el; array_stack_empty(stack) == OK; array_stack_pop(stack))
    {
        temp_el = array_stack_peek(stack);
        if (temp_el > max && (array_stack_counter_el(stack, temp_el) > \
        array_stack_counter_el(sorted_stack, temp_el)))
            max = temp_el;
    }

    return max;
}

int list_stack_max_el(number_t **head, number_t **sorted_head)
{
    if (list_stack_empty(*head) != OK)
        return STACK_EMPTY;

    int max = list_stack_peek(*head);
    for (; list_stack_counter_el(*head, max) <= list_stack_counter_el(*sorted_head, max);)
    {
        list_stack_pop(head);
        max = list_stack_peek(*head);
    }

    for (int temp_el; list_stack_empty(*head) == OK; list_stack_pop(head))
    {
        temp_el = list_stack_peek(*head);
        if (temp_el > max && (list_stack_counter_el(*head, temp_el) > \
        list_stack_counter_el(*sorted_head, temp_el)))
            max = temp_el;
    }

    return max;
}

size_t list_stack_size(number_t *head)
{
    number_t *head_copy, *head_temp;
    size_t size = 0;

    head_copy = NULL;
    head_temp = NULL;

    list_stack_copy(&head, &head_copy, &head_temp);

    for (; head_copy;)
    {
        list_stack_pop(&head_copy);
        size++;
    }

    list_stack_free(&head_copy);
    list_stack_free(&head_temp);

    return size;
}

void list_stack_free(number_t **head)
{
    number_t *next;

    for (; *head; *head = next)
    {
        next = (*head)->next;
        free(*head);
    }
}


