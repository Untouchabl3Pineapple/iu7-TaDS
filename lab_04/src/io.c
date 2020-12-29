#include "../inc/io.h"

int array_stack_init(array_stack_t *stack) 
{
    stack->top = INIT_TOP;
    stack->size = MAX_STACK_SIZE;
    stack->data = (int *)malloc(stack->size * sizeof(int));
    if (stack->data == NULL)
        return MEMORY_ALLOCATION_ERROR;

    return OK;
}

number_t *list_element_init(const int value)
{   
    number_t *node = (number_t *)malloc(sizeof(struct number_t));

    if (node)
    {
        (node)->data = value;
        (node)->next = NULL; 
    }

    return node;
}

int stack_fill(array_stack_t *stack, number_t **head)
{
    int number;

    printf("Введите количество элементов ( > 0): ");
    if (fscanf(stdin, "%d", &number) != 1)
        return STACK_FILL_ERROR;
    if (number < 1)
        return STACK_EMPTY;

    printf("Введите элементы через пробел: ");
    for (int i = 0, rc, value; i < number; i++)
    {
        if (fscanf(stdin, "%d", &value) != 1)
            return STACK_FILL_ERROR;
        
        if (array_stack_push(stack, value) != OK)
            return STACK_OVERFLOW;

        rc = list_stack_push(head, value);
        if (rc != OK)
        {
            list_stack_free(head);
            return rc;
        }
    }

    return OK;
}

void array_stack_print(array_stack_t *stack)
{   
    array_stack_t stack_copy, stack_temp;

    array_stack_init(&stack_copy);
    array_stack_init(&stack_temp);

    array_stack_copy(stack, &stack_copy, &stack_temp);
    
    printf("[ ");
    for (; array_stack_empty(&stack_copy) == OK;)
    {
        printf("%d ", array_stack_pop(&stack_copy));
    }
    printf("]\n");

    free(stack_copy.data);
    free(stack_temp.data);
}

void list_stack_print(number_t **head)
{   
    number_t *head_copy, *head_temp;

    head_copy = NULL;
    head_temp = NULL;

    list_stack_copy(head, &head_copy, &head_temp);

    printf("[ ");
    for (; list_stack_empty(head_copy) == OK;)
    {
        printf("%d ", list_stack_pop(&head_copy));
    }
    printf("]\n");

    list_stack_copy(head, &head_copy, &head_temp);

    printf("Адреса элементов стека --> ");
    printf("[ ");
    for (; list_stack_empty(head_copy) == OK; list_stack_pop(&head_copy))
    {
        printf("%p ", (void *)head_copy);
    }
    printf("]\n");

    list_stack_free(&head_copy);
    list_stack_free(&head_temp);
}

void info(void)
{
    printf("\n\x1B[32mНазначения программы:\x1B[0m\n");
    printf("Данная программа предназначена для выполнения различных операций со стеком,\n");
    printf("представленным массивом и списком\n");
    printf("\x1B[31mВНИМАНИЕ:\x1B[0m\n");
    printf("1) 4-ый и 5-ый пункты меню выполняются строго с заполненными двумя стеками\n");
    printf("2) Если при заполнении стека произошло переполнение, то стек все равно заполнится до верхней границы\n");
    printf("3) Если слиянии элементов из двух стеков в третий произошло переполнение, то третий стек станет пустым\n");
    printf("4) Если при извлечении элемента из стека произошло опустошение, то стек станет пустым\n");
    printf("5) Стек инициализируется при первом добавленном в него элементе\n");
    printf("6) Максимальный размер стека равен 20-ти элементам\n");
}

void menu(void)
{
    printf("\n\n                                == МЕНЮ ==\n\n");
    printf("1  - Добавить элементы в стеки (количество)\n");
    printf("2  - Удалить элементы из стеков (количество)\n");
    printf("3  - Вывод текущего состояния стеков\n");
    printf("4  - Отсортировать два стека в третий\n");
    printf("5  - Вывести время и память, затраченные на сортировку стеков в разных реализациях (массив и список)\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_error(const int exit_code)
{
    if (exit_code == MEMORY_ALLOCATION_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось выделить память");
    if (exit_code == STACK_OVERFLOW)
        system("echo \x1B[31mОшибка:\x1B[0m произошло переполнение стека");
    if (exit_code == STACK_UNDERFLOW)
        system("echo \x1B[31mОшибка:\x1B[0m произошло опустошение стека");
    if (exit_code == STACK_EMPTY)
        system("echo \x1B[31mОшибка:\x1B[0m пустой стек");
    if (exit_code == STACK_FILL_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m некорректные данные при заполнение стека");  
    if (exit_code == STACK_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введен номер стека для добавления элементов");
    if (exit_code == STACK_POP_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введено количество удаляемых элементов");
    if (exit_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введен номер пункта меню");
}
