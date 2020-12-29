#include "../inc/interface.h"

void info(void)
{
    printf("\n\x1B[32mНазначения программы:\x1B[0m\n");
    printf("Данная программа предназначена для выполнения операций c деревьями и хэш-таблицами\n");
}

void menu(void)
{
    printf("\n\n                                == МЕНЮ ==\n\n");
    printf("1  - Заполнить данные из файла\n");
    printf("2  - Вывести двоичное дерево поиска\n");
    printf("3  - Вывести АВЛ дерево\n");
    printf("4  - Вывести хэш-таблицу\n");
    printf("5  - Сравнить время поиска, объем памяти и количество сравнений при использовании 4-х структур данных\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_error(const int exit_code)
{
    if (exit_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверный пункт меню");
    if (exit_code == NO_DATA_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m для начала работы введите данные");
    if (exit_code == SEARCH_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введено число для поиска");
    if (exit_code == COMPARE_COUNTER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введено количество сравнений для хэш-таблицы");
    if (exit_code == FILE_OPEN_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m неверно введен файл");
}

