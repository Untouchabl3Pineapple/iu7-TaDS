#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/io.h"
#include "../inc/sort.h"
#include "../inc/main_functions.h"
#include "../inc/additional_functions.h"

int main(void)
{ 
    array_stack_t array_stack_1, array_stack_2, array_stack_res;
    number_t *head_1 = NULL, *head_2 = NULL, *head_res = NULL;
    int menu_number;

    array.len = 0;

    system("figlet -w 200 Hello, user!");
    info();
    do
    {
        menu();
        fpurge(stdin);
        int rc = fscanf(stdin, "%d", &menu_number);

        if (menu_number < 0 || menu_number > 5 || rc != 1)
        {
            print_error(MENU_NUMBER_ERROR);
            continue;
        }
        if (menu_number == 1)
        {
            int stack_number;

            printf("Введите стек (1 - первый стек, 2 - второй стек, 3 - оба стека), в который хотите добавить элементы: ");
            if (fscanf(stdin, "%d", &stack_number) != 1)
            {
                print_error(STACK_NUMBER_ERROR);
                continue;
            }
            if (stack_number < 1 || stack_number > 3)
            {
                print_error(STACK_NUMBER_ERROR);
                continue;
            }

            if (head_1 == NULL && head_2 == NULL)
            {
                if (array_stack_init(&array_stack_1) != OK)
                {
                    print_error(MEMORY_ALLOCATION_ERROR);
                    return MEMORY_ALLOCATION_ERROR;
                }
                if (array_stack_init(&array_stack_2) != OK)
                {
                    print_error(MEMORY_ALLOCATION_ERROR);
                    free(array_stack_1.data);
                    return MEMORY_ALLOCATION_ERROR;
                }
            }

            if (stack_number == 1 || stack_number == 3)
            {
                printf("\nЗаполнение 1-го стека\n");
                rc = stack_fill(&array_stack_1, &head_1);
                if (rc != OK)
                {
                    print_error(rc);
                    continue;
                }
                printf("\x1B[32mЭлементы успешно добавлены в 1-ый стек\x1B[0m\n");
            }
            if (stack_number == 2 || stack_number == 3)
            {
                printf("\nЗаполнение 2-го стека\n");
                rc = stack_fill(&array_stack_2, &head_2);
                if (rc != OK)
                {
                    print_error(rc);
                    continue;
                }
                printf("\x1B[32mЭлементы успешно добавлены во 2-ой стек\x1B[0m\n");
            }
            continue;
        }
        if (menu_number == 2)
        {
            int stack_number;
            int stack_pop_number;

            if (head_1 == NULL && head_2 == NULL)
            {
                print_error(STACK_EMPTY);
                continue;
            }

            printf("Введите стек (1 - первый стек, 2 - второй стек, 3 - оба стека), из которого хотите удалить элементы: ");
            if (fscanf(stdin, "%d", &stack_number) != 1)
            {
                print_error(STACK_NUMBER_ERROR);
                continue;
            }
            if (stack_number < 1 || stack_number > 3)
            {
                print_error(STACK_NUMBER_ERROR);
                continue;
            }

            if (stack_number == 1 || stack_number == 3)
            {
                if (head_1 == NULL)
                {
                    print_error(STACK_EMPTY);
                    continue;
                }

                printf("\nВведите количество удаляемых элементов для 1-го стека: ");
                if (fscanf(stdin, "%d", &stack_pop_number) != 1)
                {
                    print_error(STACK_POP_NUMBER_ERROR);
                    continue;
                }
                for (int i = 0; i < stack_pop_number; i++)
                {
                    if (array_stack_pop(&array_stack_1) == STACK_UNDERFLOW)
                    {
                        print_error(STACK_UNDERFLOW);
                        continue;
                    }
                    list_stack_pop(&head_1);
                }
                printf("\x1B[32mЭлементы успешно удалены из 1-го стека\x1B[0m\n");
            }
            if (stack_number == 2 || stack_number == 3)
            {
                if (head_2 == NULL)
                {
                    print_error(STACK_EMPTY);
                    continue;
                }

                printf("\nВведите количество удаляемых элементов для 2-го стека: ");
                if (fscanf(stdin, "%d", &stack_pop_number) != 1)
                {
                    print_error(STACK_POP_NUMBER_ERROR);
                    continue;
                }
                for (int i = 0; i < stack_pop_number; i++)
                {
                    if (array_stack_pop(&array_stack_2) == STACK_UNDERFLOW)
                    {
                        print_error(STACK_UNDERFLOW);
                        continue;
                    }
                    list_stack_pop(&head_2);
                }
                printf("\x1B[32mЭлементы успешно удалены из 2-го стека\x1B[0m\n");
            }
            continue;
        }
        if (menu_number == 3)
        {
            if (head_1 == NULL && head_2 == NULL)
            {
                print_error(STACK_EMPTY);
                continue;
            }

            printf("\n\x1B[32mСтеки предстваленные массивом:\x1B[0m");
            printf("\nПервый стек --> ");
            array_stack_print(&array_stack_1);
            printf("Второй стек --> ");
            array_stack_print(&array_stack_2);
            if (head_res == NULL)
            {
                printf("Отсортированное слияние двух стеков --> [ ]");
            }
            else
            {
                printf("Отсортированное слияние двух стеков --> ");
                array_stack_print(&array_stack_res);
            }

            printf("\n\x1B[32mСтеки предстваленные списком:\x1B[0m");
            printf("\nПервый стек --> ");
            list_stack_print(&head_1);
            printf("Второй стек --> ");
            list_stack_print(&head_2);
            if (head_res == NULL)
            {
                printf("Отсортированное слияние двух стеков --> [ ]");
            }
            else
            {
                printf("Отсортированное слияние двух стеков --> ");
                list_stack_print(&head_res);
            }

            printf("Массив свободных областей --> ");
            printf("[ ");
            for (int i = 0; i < array.len; i++)
            {
                printf("%p ", (void *)array.free_array_points[i]);
            }
            printf("]\n");

            continue;
        }
        if (menu_number == 4)
        {
            if (head_1 == NULL || head_2 == NULL)
            {
                print_error(STACK_EMPTY);
                continue;
            }

            if (head_res != NULL)
            {
                free(array_stack_res.data);
                list_stack_free(&head_res);
                head_res = NULL;
            }
            if (head_res == NULL)
            {
                if (array_stack_init(&array_stack_res) != OK)
                {
                    print_error(MEMORY_ALLOCATION_ERROR);
                    free(array_stack_1.data);
                    free(array_stack_2.data);
                    return MEMORY_ALLOCATION_ERROR;
                }
            }

            if (array_stack_sort(&array_stack_1, &array_stack_2, &array_stack_res) != OK)
            {
                print_error(STACK_OVERFLOW);
                continue;
            }
            list_stack_sort(&head_1, &head_2, &head_res);
            printf("\x1B[32mСортировка прошла успешно\x1B[0m\n");
            continue;
        }
        if (menu_number == 5)
        {
            if (head_1 == NULL || head_2 == NULL)
            {
                print_error(STACK_EMPTY);
                continue;
            }

            if (head_res != NULL)
            {
                free(array_stack_res.data);
                list_stack_free(&head_res);
                head_res = NULL;
            }
            if (head_res == NULL)
            {
                if (array_stack_init(&array_stack_res) != OK)
                {
                    print_error(MEMORY_ALLOCATION_ERROR);
                    free(array_stack_1.data);
                    free(array_stack_2.data);
                    return MEMORY_ALLOCATION_ERROR;
                }
            }

            struct timeval ta, te;

            gettimeofday(&ta, NULL);
            if (array_stack_sort(&array_stack_1, &array_stack_2, &array_stack_res) != OK)
            {
                print_error(STACK_OVERFLOW);
                continue;
            }
            gettimeofday(&te, NULL);
            printf("\n\x1B[32mСтек представленный массивом\x1B[0m\n");
            printf("Скорость работы: ");
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
            printf("Объем памяти: ");
            printf("%lu\n", sizeof(int) * array_stack_res.top);

            gettimeofday(&ta, NULL);
            list_stack_sort(&head_1, &head_2, &head_res);
            gettimeofday(&te, NULL);
            printf("\n\x1B[32mСтек представленный списком\x1B[0m\n");
            printf("Скорость работы: ");
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
            printf("Объем памяти: ");
            printf("%lu\n", sizeof(number_t) * list_stack_size(head_res));
        
            continue;
        }
        if (menu_number == 0)
        {
            system("figlet -w 200 Exit");

            if (head_1 != NULL)
            {
                free(array_stack_1.data);
                list_stack_free(&head_1);
            }
            if (head_2 != NULL)
            {
                free(array_stack_2.data);
                list_stack_free(&head_2);
            }
            if (head_res != NULL)
            {
                free(array_stack_res.data);
                list_stack_free(&head_res);
            }

            return OK;
        }
    } while (1);
}
