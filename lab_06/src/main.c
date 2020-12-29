#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/interface.h"
#include "../inc/memory_functions.h"
#include "../inc/io.h"
#include "../inc/balance.h"
#include "../inc/hash_get_val.h"
#include "../inc/search_functions.h"

int main(void)
{
    char filename[FILE_NAME_SIZE];

    FILE *tree_file;

    tnode_t *droot = NULL, *avlroot = NULL;

    lnode_t **hash_table_main = NULL, **hash_table_spare = NULL;
    int max_mind, max_sind;

    int menu_number;

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
            printf("Введите название файла: ");

            if (fscanf(stdin, "%s", filename) != 1)
            {
                print_error(FILE_OPEN_ERROR);
                continue;
            }

            tree_file = fopen(filename, "r");

            if (tree_file == NULL)
            {
                print_error(FILE_OPEN_ERROR);
                continue;
            }

            bin_tree_filling(&droot, &avlroot, tree_file);

            hash_table_spare = hash_table_init(hash_table_spare);
            hash_table_fill(hash_table_spare, tree_file, &max_sind, "spare");

            hash_table_main = hash_table_init(hash_table_main);
            hash_table_fill(hash_table_main, tree_file, &max_mind, "main");

            printf("\n\x1B[32mДанные успешно заполнены\x1B[0m\n");

        }
        if (menu_number == 2)
        {
            if (droot == NULL)
            {
                print_error(NO_DATA_ERROR);
                continue;
            }

            tree_print(droot, 0);
        }
        if (menu_number == 3)
        {
            if (avlroot == NULL)
            {
                print_error(NO_DATA_ERROR);
                continue;
            }
            
            tree_print(avlroot, 0);
        }
        if (menu_number == 4)
        {
            if (hash_table_main == NULL)
            {
                print_error(NO_DATA_ERROR);
                continue;
            }

            hash_table_print(hash_table_main, max_mind);
        }
        if (menu_number == 5)
        {
            if (droot == NULL || avlroot == NULL || hash_table_main == NULL \
                || hash_table_spare == NULL)
            {
                print_error(NO_DATA_ERROR);
                continue;
            }

            int val;
            printf("\nВведите число для поиска: ");
            if (fscanf(stdin, "%d", &val) != 1)
            {
                print_error(SEARCH_NUMBER_ERROR);
                continue;
            }
            printf("\n");

            int cmpc;
            printf("\nВведите количество сравнений для хэш-таблицы (> 0): ");
            if (fscanf(stdin, "%d", &cmpc) != 1)
            {
                print_error(COMPARE_COUNTER_ERROR);
                continue;
            }
            if (cmpc < 1)
            {
                print_error(COMPARE_COUNTER_ERROR);
                continue;
            }
            printf("\n");
            int counter = 0;
            int rc = hash_get_val(hash_table_main, MAIN_KEY, val, cmpc, &counter, 1);

            if (rc != NUMBER_COMPARE_ERROR && rc != EMPTY_FIELD)
                printf("[%d]--> NULL\n", rc);
            else if (rc != EMPTY_FIELD)
                printf("...\n\n\x1B[31mПревышено количество сравнений\x1B[0m\n\n");
            else
            {
                printf("\x1B[31mВведенное число не было найдено\x1B[0m\n\n");
                continue;
            }

            int numb = 0;

            if (rc == NUMBER_COMPARE_ERROR)
            {
                printf("1 - Продолжить поиск элемента в других структурах данных\n");
                printf("2 - Реструктуризировать таблицу, выбрав другую хэш-функцию\n\n");
                printf("Ответ: ");

                if (fscanf(stdin, "%d", &numb) != 1)
                {
                    print_error(MENU_NUMBER_ERROR);
                    continue;
                }
                if (numb < 1 || numb > 2)
                {
                    print_error(MENU_NUMBER_ERROR);
                    continue;
                }

                if (numb == 2)
                {
                    rc = hash_get_val(hash_table_spare, SPARE_KEY, val, cmpc, &counter, 1);

                    if (rc != NUMBER_COMPARE_ERROR && rc != EMPTY_FIELD)
                        printf("\n[%d]--> NULL\n", rc);
                    else if (rc != EMPTY_FIELD)
                        printf("...\n\n\x1B[31mПревышено количество сравнений\x1B[0m\n\n");
                    else
                    {
                        printf("\x1B[31mВведенное число не было найдено\x1B[0m\n\n");
                        continue;
                    }

                    hash_table_search(hash_table_spare, SPARE_KEY, val, cmpc, max_sind);
                }
            }
            
            if (numb == 0)
                hash_table_search(hash_table_main, MAIN_KEY, val, cmpc, max_mind);

            file_search(tree_file, val);
            tree_search(droot, val, "ДДП", tree_file);
            tree_search(avlroot, val, "АВЛ", tree_file);
        }
        if (menu_number == 0)
        {
            system("figlet -w 200 Exit");

            return OK;
        }
    } while (1);



    return OK;
}
