#include "../inc/interface.h"

void info(void)
{
    printf("\n\x1B[32mНазначения программы:\x1B[0m\n");
    printf("Данная программа предназначена для выполнения операций c графами\n");
}

void menu(void)
{
    printf("\n\n                                == МЕНЮ ==\n\n");
    printf("1  - Заполнить данные из файла\n");
    printf("2  - Найти город с минимальной суммой расстояний до остальных городов\n");
    printf("3  - Вывести время и объем памяти, затраченные на поиск города\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_error(const int exit_code)
{
    if (exit_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверный пункт меню");
    if (exit_code == FILENAME_FILL_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m введите корретное имя файла");
    if (exit_code == FILE_OPEN_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось открыть файл");
    if (exit_code == MATRIX_FILL_PARAMETR_ERROR || exit_code == MATRIX_FILL_ELEMENT_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось заполнить матрицу смежности");
    if (exit_code == FILE_MISSING_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m для начала введите файл");
}

