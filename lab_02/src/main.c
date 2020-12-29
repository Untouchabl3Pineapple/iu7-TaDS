#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define SURNAME_LENGHT 40
#define NAME_LENGHT 40
#define PHONE_NUMBER_LENGTH 15
#define ADDRESS_LENGHT 20
#define STATUS_LENGHT 10
#define POST_LENGHT 40
#define SERVICE_LENGHT 40

#define FILE_LENGHT 2000
#define FILE_NAME_LENGHT 20

#define OK 0
#define MENU_NUMBER_ERROR 1
#define FILE_READING_ERROR 2
#define STATUS_INIT_ERROR 3
#define PARSE_ARGS_ERROR 4
#define APPEND_ERROR 5
#define USER_DATA_ERROR 6
#define TABLE_OVERFLOW_ERROR 7
#define BIRHDAY_ERROR 8
#define SURNAME_FIND_ERROR 9

typedef struct
{
    char surname[SURNAME_LENGHT];
    char name[NAME_LENGHT];
    char phone_number[PHONE_NUMBER_LENGTH];
    char address[ADDRESS_LENGHT];
    char status[STATUS_LENGHT];
    union
    {
        struct
        {
            char post[POST_LENGHT];
            char service_name[SERVICE_LENGHT];
        } service;
        struct
        {
            int day;
            int month;
            int year;
        } personal;
    } type_user;
} user;

typedef struct
{
    int index;
    char surname[SURNAME_LENGHT];
} key;

void menu(void)
{
    printf("\n\n\n                                == МЕНЮ ==\n\n\n");
    printf("1  - Добавить запись в таблицу\n");
    printf("2  - Удалить запись из таблицы по значению указанного поля\n");
    printf("3  - Вывести исходную таблицу\n");
    printf("4  - Вывести текущую таблицу\n");
    printf("5  - Просмотреть отсортированную таблицу ключей при несортированной текущей таблице\n");
    printf("6  - Вывести упорядоченную текущую таблицу\n");
    printf("7  - Вывести текущую таблицу в упорядоченном виде, используя упорядоченную таблицу ключей\n");
    printf("8  - Сравнить сортировку по ключам и сортировку самой таблицы\n");
    printf("9  - Сравнить быструю сортировку и сортировку пузырьком\n");
    printf("10 - Найти всех друзей, которых необходимо поздравить с днем рождения в ближайшую неделю\n");
    printf("0  - Выйти\n");
    printf("\nВведите номер действия, которое ходите произвести: ");
}

void print_table_header(int8_t table_number)
{
    if (table_number == 1)
    {
        printf("+-------+------------------+----------------+--------------------+---------------------+---------+-------+---------+----------------+-------------+\n");
        printf("| Номер |     Фамилия      |      Имя       |       Номер        |        Адрес        |   день  | месяц |   год   |   должность    | организация |\n");
        printf("|-------|------------------|----------------|--------------------|---------------------|---------|-------|---------|----------------|-------------|\n");
    }
    else
    {
        printf("+-------+----------------------------------+------------------+\n");
        printf("| Номер |     Индекс исходной таблицы      |      Фамилия     |\n");
        printf("+-------|----------------------------------|------------------+\n");
    }
}

int8_t print_data(const user *const data_array, const int data_len)
{
    if (data_len == 0)
    {
        puts("");
        system("echo \x1B[31mТаблица пустая\x1B[0m");
        return OK;
    }

    print_table_header(1);
    for (int i = 0; i < data_len; i++)
    {
        printf("%5d", i + 1);
        printf("%15s", data_array[i].surname);
        printf("%20s", data_array[i].name);
        printf("%20s", data_array[i].phone_number);
        printf("%20s", data_array[i].address);
        if (strcmp(data_array[i].status, "0") == 0)
        {
            printf("%13d", data_array[i].type_user.personal.day);
            printf("%9d", data_array[i].type_user.personal.month);
            printf("%10d", data_array[i].type_user.personal.year);
            printf("           -");
            printf("               -\n");
        }
        else
        {
            printf("            -");
            printf("        -");
            printf("         -");
            printf("%14s", data_array[i].type_user.service.post);
            printf("%15s\n", data_array[i].type_user.service.service_name);
        }
    }

    return OK;
}

void print_error(const int error_code)
{
    if (error_code == MENU_NUMBER_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m вы ввели некорректный номер пункта меню");
    if (error_code == FILE_READING_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось прочитать файл");
    if (error_code == STATUS_INIT_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось прочитать статус человека");
    if (error_code == APPEND_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не удалось добавить новую запись");
    if (error_code == PARSE_ARGS_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m проверьте аргументы командной строки");
    if (error_code == USER_DATA_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m проверьте введенные данные");
    if (error_code == TABLE_OVERFLOW_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m произошло переполнение таблицы");
    if (error_code == BIRHDAY_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m ни у кого из друзей нет дня рождения в ближайшую неделю");
    if (error_code == SURNAME_FIND_ERROR)
        system("echo \x1B[31mОшибка:\x1B[0m не было найдено ни одного человека с данной фамилией");
}

int8_t add_entry(user *data_array, int *const data_len)
{
    int i = (*data_len)++;

    if (*data_len > FILE_LENGHT)
    {
        (*data_len)--;
        system("echo \x1B[31mБыла достигнута максимальная длина таблицы\x1B[0m");
        return OK;
    }

    printf("Введите фамилию (любую на ваш выбор): ");
    if (fscanf(stdin, "%s", data_array[i].surname) != 1)
        return APPEND_ERROR;
    printf("Введите имя (любое на ваш выбор): ");
    if (fscanf(stdin, "%s", data_array[i].name) != 1)
        return APPEND_ERROR;
    printf("Введите номер телефона (любой на ваш выбор): ");
    if (fscanf(stdin, "%s", data_array[i].phone_number) != 1)
        return APPEND_ERROR;
    printf("Введите адрес (любой на ваш выбор): ");
    if (fscanf(stdin, "%s", data_array[i].address) != 1)
        return APPEND_ERROR;
    printf("Введите статус (0 - личный, 1 - служебный): ");
    if (fscanf(stdin, "%s", data_array[i].status) != 1)
        return APPEND_ERROR;

    if (strcmp(data_array[i].status, "0") == 0)
    {
        puts("Вы выбрали статус 0 - личный:");
        printf("Введите день (число от 1 до 31 включительно): ");
        if (fscanf(stdin, "%d", &data_array[i].type_user.personal.day) != 1)
            return APPEND_ERROR;
        if (data_array[i].type_user.personal.day < 1 || data_array[i].type_user.personal.day > 31)
            return USER_DATA_ERROR;
        printf("Введите месяц (число от 1 до 12 включительно): ");
        if (fscanf(stdin, "%d", &data_array[i].type_user.personal.month) != 1)
            return APPEND_ERROR;
        if (data_array[i].type_user.personal.month < 1 || data_array[i].type_user.personal.month > 12)
            return USER_DATA_ERROR;
        printf("Введите год (число от 1 до 3000 включительно): ");
        if (fscanf(stdin, "%d", &data_array[i].type_user.personal.year) != 1)
            return APPEND_ERROR;
        if (data_array[i].type_user.personal.year < 1 || data_array[i].type_user.personal.year > 3000)
            return USER_DATA_ERROR;
        puts("");
    }
    else if (strcmp(data_array[i].status, "1") == 0)
    {
        puts("Вы выбрали статус 1 - служебный:");
        printf("Введите должность (любую на ваш выбор): ");
        if (fscanf(stdin, "%s", data_array[i].type_user.service.post) != 1)
            return APPEND_ERROR;
        printf("Введите организацию (любую на ваш выбор): ");
        if (fscanf(stdin, "%s", data_array[i].type_user.service.service_name) != 1)
            return APPEND_ERROR;
        puts("");
    }
    else
    {
        return STATUS_INIT_ERROR;
    }

    return OK;
}

void delete_entry(user *data_array, int *const data_len)
{
    int human_counter = 0;
    char temp_surname[SURNAME_LENGHT];

    printf("Введите фамилию людей, которых вы хотите убрать из таблицы: ");
    fscanf(stdin, "%s", temp_surname);
    for (int i = 0; i < *data_len; i++)
    {
        if (strcmp(data_array[i].surname, temp_surname) == 0)
        {
            human_counter++;
            for (int j = i; j < *data_len; j++)
            {
                strcpy(data_array[j].surname, data_array[j + 1].surname);
                strcpy(data_array[j].name, data_array[j + 1].name);
                strcpy(data_array[j].phone_number, data_array[j + 1].phone_number);
                strcpy(data_array[j].address, data_array[j + 1].address);
                strcpy(data_array[j].status, data_array[j + 1].status);
                if (strcmp(data_array[j + 1].status, "0") == 0)
                {
                    data_array[j].type_user.personal.day = data_array[j + 1].type_user.personal.day;
                    data_array[j].type_user.personal.month = data_array[j + 1].type_user.personal.month;
                    data_array[j].type_user.personal.year = data_array[j + 1].type_user.personal.year;
                }
                else if (strcmp(data_array[j + 1].status, "1") == 0)
                {
                    strcpy(data_array[j].type_user.service.post, data_array[j + 1].type_user.service.post);
                    strcpy(data_array[j].type_user.service.service_name, data_array[j + 1].type_user.service.service_name);
                }
            }
            i--;
        }
    }
    if (human_counter == 0)
    {
        puts("");
        print_error(SURNAME_FIND_ERROR);
    }
    *data_len -= human_counter;
}

int8_t data_fill(FILE *f, user *data_array, int *const data_len)
{
    int i;

    for (i = 0; fscanf(f, "%s", data_array[i].surname) == 1; i++)
    {
        if (i == FILE_LENGHT)
            return TABLE_OVERFLOW_ERROR;

        if (fscanf(f, "%s", data_array[i].name) != 1)
            return FILE_READING_ERROR;
        if (fscanf(f, "%s", data_array[i].phone_number) != 1)
            return FILE_READING_ERROR;
        if (fscanf(f, "%s", data_array[i].address) != 1)
            return FILE_READING_ERROR;
        if (fscanf(f, "%s", data_array[i].status) != 1)
            return FILE_READING_ERROR;

        if (strcmp(data_array[i].status, "0") == 0)
        {
            if (fscanf(f, "%d", &data_array[i].type_user.personal.day) != 1)
                return FILE_READING_ERROR;
            if (fscanf(f, "%d", &data_array[i].type_user.personal.month) != 1)
                return FILE_READING_ERROR;
            if (fscanf(f, "%d", &data_array[i].type_user.personal.year) != 1)
                return FILE_READING_ERROR;
        }
        else if (strcmp(data_array[i].status, "1") == 0)
        {
            if (fscanf(f, "%s", data_array[i].type_user.service.post) != 1)
                return FILE_READING_ERROR;
            if (fscanf(f, "%s", data_array[i].type_user.service.service_name) != 1)
                return FILE_READING_ERROR;
        }
        else
        {
            return STATUS_INIT_ERROR;
        }
    }
    if (feof(f) == 0)
        return FILE_READING_ERROR;

    *data_len = i;
    rewind(f);

    return OK;
}

void make_temp_file(const char *const temp_file_name)
{
    FILE *temp_file = fopen(temp_file_name, "w");
    fclose(temp_file);
}

void clear_file(FILE *temp_file, const char *const temp_file_name)
{
    fclose(temp_file);
    fopen(temp_file_name, "w");
    fclose(temp_file);
    fopen(temp_file_name, "r+");
}

void temp_file_fill(FILE *temp_file, const user *const data_array, const int data_len)
{
    for (int i = 0; i < data_len; i++)
    {
        fprintf(temp_file, "%s ", data_array[i].surname);
        fprintf(temp_file, "%s ", data_array[i].name);
        fprintf(temp_file, "%s ", data_array[i].phone_number);
        fprintf(temp_file, "%s ", data_array[i].address);
        fprintf(temp_file, "%s ", data_array[i].status);
        if (strcmp(data_array[i].status, "0") == 0)
        {
            fprintf(temp_file, "%d ", data_array[i].type_user.personal.day);
            fprintf(temp_file, "%d ", data_array[i].type_user.personal.month);
            if (i == data_len - 1)
                fprintf(temp_file, "%d", data_array[i].type_user.personal.year);
            else
                fprintf(temp_file, "%d\n", data_array[i].type_user.personal.year);
        }
        else if (strcmp(data_array[i].status, "1") == 0)
        {
            fprintf(temp_file, "%s ", data_array[i].type_user.service.post);
            if (i == data_len - 1)
                fprintf(temp_file, "%s", data_array[i].type_user.service.service_name);
            else
                fprintf(temp_file, "%s\n", data_array[i].type_user.service.service_name);
        }
    }
    rewind(temp_file);
}

int8_t user_find(const user *const data_array, const int data_len)
{
    int scan_day, scan_month;
    int scan_res, structure_res;
    int table_flag = 0;

    printf("Для поиска друга вы должны указать день его рождения, \
следуйте дальнейшим инструкциям\n\n");
    printf("Введите день (число от 1 до 31 включительно): ");
    if (fscanf(stdin, "%d", &scan_day) != 1)
        return USER_DATA_ERROR;
    printf("Введите месяц (число от 1 до 12 включительно): ");
    if (fscanf(stdin, "%d", &scan_month) != 1)
        return USER_DATA_ERROR;

    if (scan_day > 31 || scan_day < 1)
        return USER_DATA_ERROR;
    if (scan_month > 12 || scan_month < 1)
        return USER_DATA_ERROR;

    for (int i = 0; i < data_len; i++)
    {
        scan_res = scan_month * 30 + scan_day;
        structure_res = data_array[i].type_user.personal.month * 30 + data_array[i].type_user.personal.day;
        if (abs(scan_res - structure_res) <= 7)
        {
            table_flag = 1;
        }
    }

    if (table_flag == 0)
    {
        puts("");
        print_error(BIRHDAY_ERROR);
    }
    else
    {
        print_table_header(1);
        for (int i = 0; i < data_len; i++)
        {
            scan_res = scan_month * 30 + scan_day;
            structure_res = data_array[i].type_user.personal.month * 30 + data_array[i].type_user.personal.day;
            if (abs(scan_res - structure_res) <= 7)
            {
                printf("%5d", i + 1);
                printf("%15s", data_array[i].surname);
                printf("%20s", data_array[i].name);
                printf("%20s", data_array[i].phone_number);
                printf("%20s", data_array[i].address);
                printf("%13d", data_array[i].type_user.personal.day);
                printf("%9d", data_array[i].type_user.personal.month);
                printf("%10d", data_array[i].type_user.personal.year);
                printf("           -");
                printf("               -\n");
            }
        }
    }

    return OK;
}

int8_t parse_args(const int argc, const char **argv, int *number_args, char *file_name)
{
    if (argc == 2)
    {
        *number_args = argc;
        strcpy(file_name, argv[1]);
        return OK;
    }
    return PARSE_ARGS_ERROR;
}

void all_files_close(FILE *main_file, FILE *temp_file)
{
    fclose(main_file);
    fclose(temp_file);
}

void key_table_fill(key *table, const user *const data_array, int *const key_len, const int data_len)
{
    int i;

    for (i = 0; i < data_len; i++)
    {
        table[i].index = i;
        strcpy(table[i].surname, data_array[i].surname);
    }

    *key_len = i;
}

int key_table_compare(const void * a, const void * b)
{
    return strcmp(((key*)a)->surname, ((key*)b)->surname);
}

int data_table_compare(const void * a, const void * b)
{
    return strcmp(((user*)a)->surname, ((user*)b)->surname);
}

void key_table_qsort(key *table, const int key_len)
{
    qsort(table, key_len, sizeof(table[0]), key_table_compare);
}

void key_table_bsort(key *table, const int key_len)
{
    key temp_structure;
    for (int i = 0; i < key_len - 1; i++)
    {
        for (int j = 0; j < key_len - i - 1; j++)
        {
            if (strcmp(table[j].surname, table[j + 1].surname) > 0)
            {
                temp_structure = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp_structure;
            }
        }
    }
}

void data_table_qsort(user *data_array, const int data_len)
{
    qsort(data_array, data_len, sizeof(data_array[0]), data_table_compare);
}

void data_table_bsort(user *data_array, const int data_len)
{
    user temp_structure;
    for (int i = 0; i < data_len - 1; i++)
    {
        for (int j = 0; j < data_len - i - 1; j++)
        {
            if (strcmp(data_array[j].surname, data_array[j + 1].surname) > 0)
            {
                temp_structure = data_array[j];
                data_array[j] = data_array[j + 1];
                data_array[j + 1] = temp_structure;
            }
        }
    }
}

void key_table_print(const key *const table, const int key_len)
{
    print_table_header(2);
    for (int i = 0; i < key_len; i++)
    {
        printf("%5d", i + 1);
        printf("%20d", table[i].index);
        printf("%32s\n", table[i].surname);
    }
}

int8_t print_sorted_table_by_keys(const user *const data_array, const key *const table,\
const int data_len)
{
    if (data_len == 0)
    {
        puts("");
        system("echo \x1B[31mТаблица пустая\x1B[0m");
        return OK;
    }

    print_table_header(1);
    for (int i = 0; i < data_len; i++)
    {
        printf("%5d", i + 1);
        printf("%15s", data_array[table[i].index].surname);
        printf("%20s", data_array[table[i].index].name);
        printf("%20s", data_array[table[i].index].phone_number);
        printf("%20s", data_array[table[i].index].address);
        if (strcmp(data_array[table[i].index].status, "0") == 0)
        {
            printf("%13d", data_array[table[i].index].type_user.personal.day);
            printf("%9d", data_array[table[i].index].type_user.personal.month);
            printf("%10d", data_array[table[i].index].type_user.personal.year);
            printf("           -");
            printf("               -\n");
        }
        else
        {
            printf("            -");
            printf("        -");
            printf("         -");
            printf("%14s", data_array[table[i].index].type_user.service.post);
            printf("%15s\n", data_array[table[i].index].type_user.service.service_name);
        }
    }

    return OK;
}

int main(const int argc, const char **argv)
{
    int  test;
    int  number_args;
    char file_name[FILE_NAME_LENGHT];
    char temp_file_name[FILE_NAME_LENGHT] = { "table_temp.txt" };
    int  data_len, key_len;
    int  menu_number;
    user data_array[FILE_LENGHT];
    key table[FILE_LENGHT];

    if (parse_args(argc, argv, &number_args, file_name) != OK)
    {
        print_error(PARSE_ARGS_ERROR);
        return PARSE_ARGS_ERROR;
    }

    FILE *main_file = fopen(file_name, "r");
    if (main_file == NULL)
    {
        print_error(FILE_READING_ERROR);
        return FILE_READING_ERROR;
    }
    make_temp_file(temp_file_name);
    FILE *temp_file = fopen(temp_file_name, "r+");

    test = data_fill(main_file, data_array, &data_len);
    if (test != OK)
    {
        print_error(test);
        return test;
    }
    temp_file_fill(temp_file, data_array, data_len);

    system("figlet -w 200 Hello, user!");
    do
    {
        menu();
        fpurge(stdin);
        int rc = fscanf(stdin, "%d", &menu_number); // буква или цифра не из меню

        if (menu_number < 0 || menu_number > 10 || rc != 1)
        {
            puts("");
            print_error(MENU_NUMBER_ERROR);
            continue;
        }
        if (menu_number == 1)
        {
            system("figlet -w 200 Add an entry to the table");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            test = add_entry(data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                continue;
            }
            temp_file_fill(temp_file, data_array, data_len);
        }
        if (menu_number == 2)
        {
            system("figlet -w 200 Delete a record from the table by the value of the specified field");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            clear_file(temp_file, temp_file_name);
            delete_entry(data_array, &data_len);
            temp_file_fill(temp_file, data_array, data_len);
        }
        if (menu_number == 3)
        {
            system("figlet -w 200 Output the source table");
            test = data_fill(main_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            print_data(data_array, data_len);
        }
        if (menu_number == 4)
        {
            system("figlet -w 200 Display the current table");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            print_data(data_array, data_len);
        }
        if (menu_number == 5)
        {
            system("figlet -w 200 View a sorted key table when the current table is unsorted");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            key_table_fill(table, data_array, &key_len, data_len);
            key_table_qsort(table, key_len);
            key_table_print(table, key_len);
        }
        if (menu_number == 6)
        {
            system("figlet -w 200 Ordered to withdraw the current table");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            data_table_qsort(data_array, data_len);
            print_data(data_array, data_len);
        }
        if (menu_number == 7)
        {
            system("figlet -w 200 Output the current table in an ordered form using an ordered key table");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            key_table_fill(table, data_array, &key_len, data_len);
            key_table_qsort(table, key_len);
            print_sorted_table_by_keys(data_array, table, data_len);
        }
        if (menu_number == 8)
        {
            system("figlet -w 200 Compare sorting by keys and sorting the table itself");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            key_table_fill(table, data_array, &key_len, data_len);

            puts("");
            puts("");
            struct timeval ta, te;

            printf("\x1B[32mРазмерность:              %d\x1B[0m\n", data_len);
            gettimeofday(&ta, NULL);
            key_table_qsort(table, key_len);
            gettimeofday(&te, NULL);
            printf("\x1B[32mСортировка по ключам:     %lf sec\x1B[0m\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);

            gettimeofday(&ta, NULL);
            data_table_qsort(data_array, data_len);
            gettimeofday(&te, NULL);
            printf("\x1B[32mСортировка самой таблицы: %lf sec\x1B[0m\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
        }
        if (menu_number == 9)
        {
            
            system("figlet -w 200 Compare quick sort and bubble sort");
            puts("");
            puts("");
            struct timeval ta, te;

            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            key_table_fill(table, data_array, &key_len, data_len);

            printf("\x1B[32mОбъем занимаемой памяти:\x1B[0m\n");
            printf("Количество записей: %d\n", data_len);
            printf("Основная таблица:   %lu\n", sizeof(data_array) * data_len);
            printf("Таблица ключей:     %lu\n", sizeof(table) * key_len);
            
            puts("");
            puts("");

            printf("\x1B[32mБыстрая сортировка\x1B[0m\n");
            printf("Количество записей: %d\n", data_len);
            printf("Таблица ключей:     ");
            gettimeofday(&ta, NULL);
            key_table_qsort(table, key_len);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);

            printf("Текущая таблица:    ");
            gettimeofday(&ta, NULL);
            data_table_qsort(data_array, data_len);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);

            puts("");
            puts("");

            printf("\x1B[32mСортировка пузырьком\x1B[0m\n");
            printf("Количество записей: %d\n", data_len);
            printf("Таблица ключей:     ");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            key_table_fill(table, data_array, &key_len, data_len);
            gettimeofday(&ta, NULL);
            key_table_bsort(table, key_len);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);

            printf("Текущая таблица:    ");
            test = data_fill(temp_file, data_array, &data_len);
            gettimeofday(&ta, NULL);
            data_table_bsort(data_array, data_len);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
        }
        if (menu_number == 10)
        {
            system("figlet -w 200 Find all your friends who need to be congratulated on their birthday in the next week");
            test = data_fill(temp_file, data_array, &data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
                return test;
            }
            test = user_find(data_array, data_len);
            if (test != OK)
            {
                puts("");
                print_error(test);
            }
        }
        if (menu_number == 0)
        {
            system("figlet -w 200 Exit");
            all_files_close(main_file, temp_file);
            return OK;
        }
    } while (1);
}
