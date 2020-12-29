#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/io.h"
#include "../inc/memory_functions.h"
#include "../inc/vector_queue.h"
#include "../inc/device.h"

int main(void)
{
    uint64_t start, end;
    vector_q vector;
    node_t *tail = NULL;

    int menu_number;

    array.len = 0;

    system("figlet -w 200 Hello, user!");
    info();
    do
    {
        menu();
        fpurge(stdin);
        int rc = fscanf(stdin, "%d", &menu_number);

        if (menu_number < 0 || menu_number > 4 || rc != 1)
        {
            print_error(MENU_NUMBER_ERROR);
            continue;
        }
        if (menu_number == 1)
        {
            printf("\n\x1B[32mВектор\x1B[0m\n");
            start = tick();
            fill_vdata(&vector, 1000);
            end = tick();
            printf("Время добавления элемента: %llu\n", (end - start) / 1000);
            start = tick();
            del_vdata(&vector);
            end = tick();
            printf("Время удаления элемента: %llu\n\n", (end - start) / 1000);

            printf("\x1B[32mСписок\x1B[0m\n");
            start = tick();
            fill_ldata(&tail, 1000);
            end = tick();
            printf("Время добавления элемента: %llu\n", (end - start) / 1000);
            start = tick();
            del_ldata(&tail);
            end = tick();
            printf("Время удаления элемента: %llu\n", (end - start) / 1000);
        }
        if (menu_number == 2)
        {
            int number;

            printf("Введите количество элементов для подсчета количества памяти (> 0): ");

            if (fscanf(stdin, "%d", &number) != 1)
            {
                print_error(NUMBER_ERROR);
                continue;
            }
            if (number < 1)
            {
                print_error(NUMBER_ERROR);
                continue;
            }

            fill_vdata(&vector, number);
            fill_ldata(&tail, number);

            printf("\n\x1B[32mВектор: \x1B[0m");
            printf("Объем занимаемой памяти: %zu\n", sizeof(int) * (vector.lelp - vector.felp + 1));
            printf("\x1B[32mСписок: \x1B[0m");
            printf("Объем занимаемой памяти: %zu\n", (sizeof(int) + sizeof(node_t)) * lsize(tail));

            del_vdata(&vector);
            del_ldata(&tail);
        }
        if (menu_number == 3)
        {
            fill_ldata(&tail, 10);
            array.len--;

            for (; array.len != -1; array.len--)
            {
                printf("%p\n", (void *)array.free_array_points[array.len]);
            }

            del_ldata(&tail);

            continue;
        }
        if (menu_number == 4)
        {
            srand(time(NULL));

            vector_model(&vector, 0, 5, 0 ,4);

            continue;
        }
        if (menu_number == 0)
        {
            system("figlet -w 200 Exit");

            free(vector.data);
            lfree(tail);

            return OK;
        }
    } while (1);
}
