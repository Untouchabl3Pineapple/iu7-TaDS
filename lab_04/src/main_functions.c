#include "../inc/main_functions.h"

int array_stack_push(array_stack_t *stack, const int value)
{
    if (stack->top >= stack->size)
        return STACK_OVERFLOW;

    stack->data[stack->top] = value;
    stack->top++;

    return OK;
}

int list_stack_push(number_t **head, const int value)
{
    number_t *node = list_element_init(value);
    if (node == NULL)
        return MEMORY_ALLOCATION_ERROR;

    node->next = *head;
    *head = node;

    return OK;
}

int array_stack_pop(array_stack_t *stack)
{
    if (stack->top < 1)
        return STACK_UNDERFLOW;

    stack->top--;

    return stack->data[stack->top];
}

int list_stack_pop(number_t **head) 
{
    int head_value;
    number_t* temp_node;

    if (*head == NULL) 
        return STACK_UNDERFLOW;

    if (array.len < MAX_LEN_ARRAY_FREE - 1)
    {
        array.free_array_points[array.len] = *head;
        array.len++;
    }
    temp_node = *head;
    head_value = temp_node->data;
    *head = (*head)->next;
    // free(temp_node);
    // printf("BOMBA\n");

    return head_value;
}

int array_stack_peek(array_stack_t *stack)
{
    if (stack->top < 1) 
        return STACK_UNDERFLOW;

    return stack->data[stack->top - 1];
}

int list_stack_peek(number_t *head)
{
    if (head == NULL)
        return STACK_UNDERFLOW;

    return head->data;
}

int array_stack_empty(array_stack_t *stack)
{
    if (stack->top < 1)
        return STACK_EMPTY;

    return OK;
}

int list_stack_empty(number_t *head)
{
    if (head == NULL)
        return STACK_EMPTY;

    return OK;
}
