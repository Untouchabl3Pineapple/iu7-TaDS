#include "../inc/io.h"

int fill_vdata(vector_q *vector, const int number)
{
    if (vector == NULL)
        return NULL_POINTER;

    vector_init(vector);

    for (int i = 0, rc; i < number; i++)
    {
        rc = vpush(vector, i);

        if (rc != OK)
            return NULL_POINTER;
    }

    return OK;
}

int del_vdata(vector_q *vector)
{
    if (vector == NULL)
        return NULL_POINTER;

    for (int i = 0, rc; i < 1000; i++)
    {
        rc = vpop(vector);

        if (rc == QUEUE_UNDERFLOW)
            return QUEUE_UNDERFLOW;
    }

    return OK;
}

int fill_ldata(node_t **tail, const int number)
{
    if (tail == NULL)
        return NULL_POINTER;

    for (int i = 0, rc; i < number; i++)
    {
        rc = lpush(tail, i);

        if (array.len < MAX_LEN_ARRAY_FREE - 1)
        {
            array.free_array_points[array.len] = *tail;
            array.len++;
        }

        if (rc != OK)
            return NULL_POINTER;
    }

    return OK;
}

int del_ldata(node_t **tail)
{
    if (tail == NULL)
        return NULL_POINTER;

    for (int i = 0, rc; i < 1000; i++)
    {
        rc = lpop(tail);

        if (rc == QUEUE_UNDERFLOW)
            return QUEUE_UNDERFLOW;
    }

    return OK;
}

int print_vdata(vector_q *vector)
{
    if (vector == NULL)
        return NULL_POINTER;

    vector_q vector_copy, vector_temp;

    vcopy(vector, &vector_copy, &vector_temp);

    for (; vempty(&vector_copy) == OK; printf("%d ", vpop(&vector_copy)));

    printf("\n");

    free(vector_copy.data);
    free(vector_temp.data);

    return OK;
}

int print_ldata(node_t **tail)
{   
    if (tail == NULL || *tail == NULL)
        return NULL_POINTER;

    node_t *tail_copy, *tail_temp;

    lcopy(tail, &tail_copy, &tail_temp);

    for (; lempty(tail_copy) == OK; printf("%d ", lpop(&tail_copy)));

    printf("\n");

    lfree(tail_copy);
    lfree(tail_temp);

    return OK;
}

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void info(void)
{
    printf("\n\x1B[32mНазначения программы:\x1B[0m\n");
    printf("Данная программа предназначена для выполнения операций с очередью,\n");
    printf("представленной массивом и списком\n");
}

void menu(void)
{
    printf("\n\n                                == МЕНЮ ==\n\n");
    printf("1  - Вывести время для добавления и удаление элемента из очереди в разных реализациях\n");
    printf("2  - Вывести память, затраченную на введенное количество элементов в разных реализациях\n");
    printf("3  - Отследить фрагментацию памяти\n");
    printf("4  - Смоделировать процесс обслуживания первых 1000 заявок\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_error(const int exit_code)
{
    if (exit_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверный пункт меню");
    if (exit_code == NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m введено неверное количество элементов");
}
