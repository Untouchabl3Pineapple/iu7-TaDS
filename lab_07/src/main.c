#include "../inc/time.h"
#include "../inc/interface.h"
#include "../inc/data_structures.h"
#include "../inc/constants.h"
#include "../inc/memory_functions.h"
#include "../inc/io.h"
#include "../inc/process.h"

int main(void)
{
    char filenametxt[FILE_NAME_SIZE];
    FILE *filetxt = NULL;
    graph_t graph;

    int menu_number;

    system("figlet -w 200 Hello, user!");
    info();
    do
    {
        menu();
        fpurge(stdin);
        int rc = fscanf(stdin, "%d", &menu_number);

        if (menu_number < 0 || menu_number > 3 || rc != 1)
        {
            print_error(MENU_NUMBER_ERROR);
            continue;
        }
        if (menu_number == 1)
        {
            printf("Введите название файла: ");

            if (fscanf(stdin, "%s", filenametxt) != 1)
            {
                print_error(FILENAME_FILL_ERROR);
                continue;
            }

            filetxt = fopen(filenametxt, "r");
            if (filetxt == NULL)
            {
                print_error(FILE_OPEN_ERROR);
                continue;
            }

            rc = matrix_fill(&graph, filetxt);
            if (rc != OK)
            {
                print_error(rc);
                continue;
            }

            printf("\n\x1B[32mДанные успешно заполнены\x1B[0m\n");
        }
        if (menu_number == 2)
        {
            if (filetxt == NULL)
            {
                print_error(FILE_MISSING_ERROR);
                continue;
            }

            paths_fill(graph);

            graph_vis(graph);
        }
        if (menu_number == 3)
        {
            if (filetxt == NULL)
            {
                print_error(FILE_MISSING_ERROR);
                continue;
            }

            uint64_t start = tick(), end;

            for (int i = 0; i < 1000; i++)
            {
                paths_fill(graph);
            }

            end = tick();

            printf("\nКоличество элементов: %d\n", graph.size);
            printf("Время: %llu\n", (end - start) / 1000);
            printf("Объем памяти: %lu\n", sizeof(int) * graph.size * graph.size * 2 + sizeof(graph_t));


        }
        
        if (menu_number == 0)
        {
            system("figlet -w 200 Exit");

            free_graph(&graph);

            return OK;
        }
    } while (1);
}
