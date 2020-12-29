#include "menu_and_errors.h"
#include "io.h"

void menu(void)
{
    printf("\n\n                                == МЕНЮ ==\n\n");
    printf("1  - Ввести две матрицы с клавиатуры\n");
    printf("2  - Сгенерировать две матрицы с заданным процентом разреженности\n");
    printf("3  - Сложить две матрицы в стандартном формате\n");
    printf("4  - Сложить две матрицы в столбцовом формате\n");
    printf("5  - Вывести две матрицы в обычном формате\n");
    printf("6  - Вывести две матрицы в столбцовом формате\n");
    printf("7  - Сравнить время выполнения операций и объем памяти при сложении матриц в разных форматах\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_error(const int error_code)
{
    if (error_code == IO_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m вы ввели матрицу некорректно");
    if (error_code == EMPTY_MATRIX_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m вы не ввели матрицы");
    if (error_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m вы ввели неверный пункт меню");
    if (error_code == MATRIX_GENERATE_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m вы ввели неверные данные для генерации матрицы");
}
