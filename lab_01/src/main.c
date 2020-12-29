#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define INT_LEN 34
#define FLOAT_LEN 42
#define MANTISSA_MAX_LEN 30
#define MANTISSA_MIN_LEN 1
#define ORDER_MAX_LEN 5
#define ORDER_MIN_LEN 1
 
#define INT_LEN 34
#define SIGNS_LEN 3
#define MANTISSA_LEN 31
#define MANTISSA_LEN_STRUCTURE 35
#define ORDER_LEN 6
 
#define OK 0
#define FGETS_ERROR 1
#define INTEGER_LEN_ERROR 2
#define FLOAT_LEN_ERROR 3
#define CHARACTER_ERROR 4
#define MANTISSA_LEN_ERROR 5
#define ORDER_LEN_ERROR 6
#define NUMBER_CHECK_ERORR 7
#define CHARACTER_LOCATION_ERROR 8
#define EXTRA_ZEROS_ERROR 9
#define DIVISION_BY_ZERO_ERROR 10
#define OVERFLOW_ORDER_ERROR 11
#define MACHINE_ZERO_ERROR 12

#define NULL_PRINT 2
 
typedef struct
{
    char signs[SIGNS_LEN];
    char mantissa[MANTISSA_LEN_STRUCTURE];
    int order;
} description;
 
int number_characters(char *const str, const char el, const int str_len)
{
    int el_counter = 0;
 
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == el)
            el_counter++;
    }
 
    return el_counter;
}
 
int number_check(char *const str, const int start_index,\
const int end_index)
{
    for (int i = start_index; i < end_index; i++)
    {
        if ('0' < str[i] && str[i] > '9')
            return NUMBER_CHECK_ERORR;
    }
 
    return OK;
}
 
int index_find(char *const str, const char el, const int str_len)
{
    int i;
 
    for (i = 0; str[i] != el; i++);
 
    return i;
}
 
void structure_filling(char *const floating_point_number)
{
    description float_number;
 
    memset(float_number.signs, '\0', SIGNS_LEN);
    memset(float_number.mantissa, '\0', MANTISSA_LEN);
 
    char temp_order[ORDER_LEN] = { '\0' };
 
    int floating_point_number_len = strlen(floating_point_number);
    int exp_index = index_find(floating_point_number, 'E', floating_point_number_len);
    int order_len = floating_point_number_len - exp_index - 3;
    strncpy(float_number.signs, &floating_point_number[0], 1);
    strncat(float_number.signs, &floating_point_number[exp_index + 1], 1);
    int temp_fl = 0;
    if (exp_index == 32)
    {
        exp_index--;
        temp_fl = 1;
    }
    strncpy(float_number.mantissa, &floating_point_number[1], exp_index - 1);
    strncpy(temp_order, &floating_point_number[exp_index + 2], order_len);
    float_number.order = atoi(temp_order);
    if (temp_fl == 1)
        float_number.order++;
}
 
void create_integer_number(void)  // Example: 24234.   itoa
{
    description float_number;
 
    int mantissa_len = strlen(float_number.mantissa);
    int point_index = index_find(float_number.mantissa, '.', mantissa_len);
 
    // converting to an integer and decrease/increase the order
    while (mantissa_len - point_index - 1 >= 1) 
    {
        if (mantissa_len - point_index - 1 == 1 && float_number.mantissa[point_index + 1] == '0')
            break;
        if (float_number.signs[1] == '+')
            float_number.order--;
        else
            float_number.order++;
        float_number.mantissa[point_index] = float_number.mantissa[point_index + 1];
        float_number.mantissa[point_index + 1] = '.';
        point_index = index_find(float_number.mantissa, '.', mantissa_len);
    }
    // removing leading zeros
    char temp_string[INT_LEN] = { '\0' };
    if (float_number.mantissa[0] == '0' && mantissa_len != 1)
    {
        for (int i = 0; float_number.mantissa[i] == '0'; i++)
        {
            if (float_number.mantissa[i + 1] != '0')
                strcpy(temp_string, &float_number.mantissa[i + 1]);
        }
        strcpy(float_number.mantissa, temp_string);
    }
}
 
int number_convert(char number)
{
    return number - '0';
}
 
void subtraction(char *first_number, char *second_number) // atoi   +3221  -10.0E-1
{
    char temp_chr[2] = { '\0' }; 
    int res, flag, i;
    int first_number_len = strlen(first_number); //  22   10
    int second_number_len = strlen(second_number);
 
    flag = 0;
 
    for (i = 0; i < second_number_len; i++)
    {
        res = number_convert(first_number[first_number_len - 1 - i]) - \
        number_convert(second_number[second_number_len - 1 - i]) - flag;
        flag = 0;
        if (res < 0)
        {
            res += 10;
            flag = 1;
        }
        sprintf(temp_chr, "%d", res);
        first_number[first_number_len - 1 - i] = temp_chr[0];
    }
    if (flag == 1)
    {
        res = number_convert(first_number[first_number_len - 1 - i]) - flag;
        if (res == - 1)
        {
            first_number[first_number_len - i - 1] = '9';
            sprintf(temp_chr, "%d", number_convert(first_number[first_number_len - i - 2] - flag));
            first_number[first_number_len - i - 2] = temp_chr[0];
        }
        else
        {
            sprintf(temp_chr, "%d", res);
            first_number[first_number_len - i - 1] = temp_chr[0];
        }
    }

    // removing leading zeros
    char temp_string[INT_LEN] = { '\0' };
    if (first_number[0] == '0' && first_number_len != 1)
    {
        for (int i = 0; first_number[i] == '0'; i++)
        {
            if (first_number[i + 1] != '0')
                strcpy(temp_string, &first_number[i + 1]);
        }
        strcpy(first_number, temp_string);
    }
}
 
int numbers_compare(char *first_number, char *second_number) // 0 - =; 1 - >; 2 - < 
{
    int first_number_len = strlen(first_number);
    int second_number_len = strlen(second_number);
 
    if (first_number_len > second_number_len)
        return 1;
    if (first_number_len < second_number_len)
        return 2;
    for (int i = 0; i < first_number_len; i++)
    {
        if (strncmp(&first_number[i], &second_number[i], 1) > 0)
            return 1;
        if (strncmp(&first_number[i], &second_number[i], 1) < 0)
            return 2; 
    }
    return 0;
}
 
int division_two_numbers(char *const integer_number)
{
    description float_number;

    integer_number[strlen(integer_number) - 1] = '\0'; // ! made for a length equal to 6
    // bringing numbers to a normalized mind
    char numerator[INT_LEN + 5] = { '\0' };
    char denominator[MANTISSA_LEN + 5] = { '\0' };
    char order_string[ORDER_LEN + 5] = { '\0' };
    sprintf(order_string, "%d", float_number.order);
 
    strcpy(numerator, &integer_number[1]);
    if (float_number.mantissa[strlen(float_number.mantissa) - 1] != '0')
        strncpy(denominator, float_number.mantissa, strlen(float_number.mantissa) - 1);
    else
        strncpy(denominator, float_number.mantissa, strlen(float_number.mantissa) - 2);
 
    // _________________________________________________________________________
 
    char temp_denominator_first[MANTISSA_LEN + 5] = { '\0' };
    char temp_denominator_second[MANTISSA_LEN + 5] = { '\0' };
    char integer_result[MANTISSA_LEN + 5] = { '\0' };
    char float_result[MANTISSA_LEN + 5] = { '\0' };;
    char temp_digit[MANTISSA_LEN + 5] = { '\0' };
    int counter, null_counter = 0;
    int flag_on_int_res = 0, flag_on_float_res = 0, temp_flag = 0, compare_flag = 0;
 
    if (numerator[0] == '0')
    {
        puts("");
        puts("");
        puts("");
        printf("Результат: ");
        printf("+0.0E+0");

        return NULL_PRINT;
    }
    if (numbers_compare(numerator, denominator) == 0)
    {
        temp_flag = 1;
        integer_result[0] = '1';
    }
    else
    {
        while (numbers_compare(numerator, denominator) == 1 && \
        strlen(integer_result) < MANTISSA_LEN)
        {
            flag_on_int_res = 1;
            memset(temp_denominator_first, '\0', MANTISSA_LEN);
            memset(temp_denominator_second, '\0', MANTISSA_LEN);
            strcpy(temp_denominator_first, denominator);
            counter = 0;
 
            while (numbers_compare(numerator, denominator) == 1)
            {
                strcat(denominator, "0");
            }
 
            strncpy(temp_denominator_second, denominator, strlen(denominator) - 1);
            strcpy(denominator, temp_denominator_second);
 
            while (numbers_compare(numerator, denominator) == 1)
            {
                subtraction(numerator, denominator);
                counter++;
            }
            if (numbers_compare(numerator, denominator) == 0)
            {
                counter++;
                compare_flag++;
                if (compare_flag > 1)
                {
                    strncat(integer_result, "0", 1);
                    strcpy(denominator, temp_denominator_first);
                    continue;
                }
            }
            sprintf(temp_digit, "%d", counter);
            strncat(integer_result, temp_digit, strlen(temp_digit));
            strcpy(denominator, temp_denominator_first);
        }

        compare_flag = 0;

        while (numbers_compare(numerator, denominator) == 2 && strlen(float_result)\
        + strlen(integer_result) < MANTISSA_LEN)
        {
            flag_on_float_res = 1;
            counter = 0;
            null_counter = 0;

            while (numbers_compare(numerator, denominator) == 2)
            {
                strcat(numerator, "0");
                null_counter++;
            }
            null_counter--;
            while (numbers_compare(numerator, denominator) == 1)
            {
                subtraction(numerator, denominator);
                counter++;
            }

            if (numbers_compare(numerator, denominator) == 0)
            {
                compare_flag = 1;
                counter++;
            }

            int flag_ret = 0;
            for (int i = 0; i < null_counter; i++)
            {
                if (strlen(float_result) + strlen(integer_result) >= MANTISSA_LEN)
                {
                    flag_ret = 1;
                    break;
                }
                strncat(float_result, "0", 1);

            }
            if (flag_ret == 1)
            {
                break;
            }

            sprintf(temp_digit, "%d", counter);
            strncat(float_result, temp_digit, 1);
        }
    }
 
    // _________________________________________________________________________
 
    if (flag_on_int_res == 0 && temp_flag == 0)
        integer_result[0] = '0';
    if (flag_on_float_res == 0)
        float_result[0] = '0';

    if (float_number.signs[1] == '-')
        float_number.order = float_number.order * (- 1); // !!!!!!!!!!!!!!!
    float_number.order = float_number.order * (- 1);

    sprintf(order_string, "%d", float_number.order);
 
    if ((integer_number[0] == '+' && float_number.signs[0] == '-') ||\
    (integer_number[0] == '-' && float_number.signs[0] == '+'))
    {
        float_number.signs[0] = '-';
    }
    else
    {
        float_number.signs[0] = '+';
    }
    int flag_end = 0;
    char temp_float[MANTISSA_LEN + 5] = { '\0' };
    if (float_result[0] == '0' && strlen(float_result) != 1)
    {
        for (int i = 0; i < strlen(float_result); i++)
        {
            if (float_result[i] == '0' && flag_end == 0)
            {
                float_number.order--;
            }
            else
            {
                strncat(temp_float, &float_result[i], 1);
                flag_end = 1;
            }
        }
        strcpy(float_result, temp_float);
    }

    if (integer_result[0] != '0')
    {
        strcpy(float_number.mantissa, "0");
        strcat(float_number.mantissa, ".");
        float_number.order += strlen(integer_result);
        for (int i = 0; i < strlen(integer_result); i++)
        {
            int flagg = 0;
            if (integer_result[i] == '0')
            {
                for (int j = i; j < strlen(integer_result); j++)
                {
                    if (integer_result[j] != '0')
                    {
                        flagg = 1;
                        break;
                    }
                }
                if (flagg == 0 && integer_result[i] == '0')
                {
                    integer_result[i] = '\0';
                    break;
                }
            }
        }
        strcat(float_number.mantissa, integer_result);
        if (float_result[0] == '0' && strlen(float_result) == 1);
        else
            strcat(float_number.mantissa, float_result);
    }
    else 
    {
        strcpy(float_number.mantissa, integer_result);
        strcat(float_number.mantissa, ".");
        for (int i = 0; i < strlen(float_result); i++)
        {
            int flagg = 0;
            if (float_result[i] == '0')
            {
                for (int j = i; j < strlen(float_result); j++)
                {
                    if (float_result[j] != '0')
                    {
                        flagg = 1;
                        break;
                    }
                }
                if (flagg == 0 && float_result[i] == '0')
                {
                    float_result[i] = '\0';
                    break;
                }
            }
        }
        strcat(float_number.mantissa, float_result);
    }
 
    return OK;
}
 
int normalized_output(void)
{
    description float_number;
    char temp_char[3] = { '\0' };

    if (strlen(float_number.mantissa) == 33)
    {
        if (number_convert(float_number.mantissa[32]) >= 5)
        {
            int i;
            int tf = 0;
            for (i = strlen(float_number.mantissa) - 2; float_number.mantissa[i] == '9'; i--)
            {
                tf = 1;
                float_number.mantissa[i] = '\0' ;
            }
            if (tf == 1)
            {
                sprintf(temp_char, "%d", number_convert(float_number.mantissa[i]) + 1);
                float_number.mantissa[i] = temp_char[0];
            }
            else
            {
                sprintf(temp_char, "%d", number_convert(float_number.mantissa[31]) + 1);
                float_number.mantissa[31] = temp_char[0];
                float_number.mantissa[32] = '\0';
            }
        }
        else
            float_number.mantissa[32] = '\0';
    }

    if (float_number.order > 99999)
        return OVERFLOW_ORDER_ERROR;
    if (float_number.order < - 99999)
        return MACHINE_ZERO_ERROR;

    puts("");
    puts("");
    puts("");
    printf("Результат: ");
    if (float_number.order >= 0)
        printf("%c%sE+%d\n", float_number.signs[0], float_number.mantissa, float_number.order);
    else
        printf("%c%sE%d\n", float_number.signs[0], float_number.mantissa, float_number.order);

    return OK;
}
 
void print_invite(void)
{
    printf("\n%150s\n\n", "=== Деление целого и действительного числа, не помещающихся в разрядную сетку ===");
    printf("%60s\n", "ПРАВИЛА ВВОДА");
    puts("1. Оба числа вводятся с знаком плюс (+) или минус (-)");
    puts("2. Для целого числа:");
    puts("2.1. После знака обязательно присутствие корректного целого числа");
    puts("2.2. Целое число может содержать не более 30 цифр");
    puts("3. Для действительного числа:");
    puts("3.1. Степень числа так же должна быть обязательно записана со знаком плюс (+) или минус (-)");
    puts("3.2. Также обязательно наличие следующих символов: '. и E' E строго с большой");
    puts("3.3. В записи порядка должна содержаться хотя бы одна цифра");
    puts("3.4. Мантисса может содержать не более 30 цифр");
    puts("3.5. Порядок может содержать не более 5 цифр");
    puts("");
    puts("Пример валидного ввода целого числа: +35");
    puts("Пример валидного ввода действительного числа: +35.E-5 или +35.0E-5");
    puts("");
    puts("Для удобства при вводе чисел вам будет предоставлена специальная линейка,");
    puts("с помощью которой вы сможете увидеть количество введенных вами цифр");
    puts("");
}

void print_error(const int error_code)
{
    if (error_code == FGETS_ERROR)
        printf("При записи числа произошла ошибка");
    if (error_code == INTEGER_LEN_ERROR)
        printf("Превышено допустимое количество символов в целом числе");
    if (error_code == FLOAT_LEN_ERROR)
        printf("Превышено допустимое количество символов в действительном числе");
    if (error_code == CHARACTER_ERROR)
        printf("Проверьте запись следующий символов: + - . E");
    if (error_code == MANTISSA_LEN_ERROR)
        printf("Проверьте количество символов в мантиссе числа");
    if (error_code == ORDER_LEN_ERROR)
        printf("Проверьте количество символов в порядке числа");
    if (error_code == NUMBER_CHECK_ERORR)
        printf("Проверьте число на предмет записи лишних символов");
    if (error_code == CHARACTER_LOCATION_ERROR)
        printf("Проверьте последовательность написания следующих символов: + - . E");
    if (error_code == EXTRA_ZEROS_ERROR)
        printf("Проверьте число на наличие лишних нулей");
    if (error_code == DIVISION_BY_ZERO_ERROR)
        printf("Деление на нуль запрещено");
    if (error_code == OVERFLOW_ORDER_ERROR)
        printf("Произошло переполнение порядка");
    if (error_code == MACHINE_ZERO_ERROR)
        printf("Машинный нуль");
}
 
int condition_test(char *const integer_number, char *const floating_point_number)
{
    printf("%23d %8d %9d %9d\n", 1, 10, 20, 30);
    printf("%54s", "±|--------|---------|---------|\n");
    printf("Введите целое число: ");
    // integer_number size check
    if (fgets(integer_number, INT_LEN, stdin) == NULL) // Error: 33
        return FGETS_ERROR;
    int integer_number_len = strlen(integer_number);
    if (integer_number_len == INT_LEN - 1)
        return INTEGER_LEN_ERROR;
 
    // integer_number element check
    if (number_characters(integer_number, '+', integer_number_len) + \
    number_characters(integer_number, '-', integer_number_len) != 1)
        return CHARACTER_ERROR;
    if (number_characters(integer_number, '.', integer_number_len) == 1)
        return CHARACTER_ERROR;
    if (number_characters(integer_number, 'E', integer_number_len) == 1)
        return CHARACTER_ERROR;
    if (number_characters(integer_number, ',', integer_number_len) == 1)
        return CHARACTER_ERROR;
 
    // integer_number check + location check
    if (integer_number[0] != '+' && integer_number[0] != '-')
        return CHARACTER_LOCATION_ERROR;
    if (number_check(integer_number, 1, integer_number_len) != OK)
        return NUMBER_CHECK_ERORR;
 
    // the extra zeros check
    if (integer_number[1] == '0' && integer_number_len != 3)
        return EXTRA_ZEROS_ERROR;
 
    // __________________________________________________________________________
    printf("\n%58s %25s\n", "мантисса", "степень");
    printf("%32d %8d %9d %9d %2d %3d\n", 1, 10, 20, 30, 1, 5);
    printf("%71s", "±|--------|---------|---------|E±|---|\n");
    printf("Введите действительное число: ");
    // floating_point_number size check
    if (fgets(floating_point_number, FLOAT_LEN, stdin) == NULL) // Error: 41
        return FGETS_ERROR;
    int floating_point_number_len = strlen(floating_point_number);
    int point_index = index_find(floating_point_number, '.', floating_point_number_len);
    int exp_index = index_find(floating_point_number, 'E', floating_point_number_len);
    if (floating_point_number_len == FLOAT_LEN - 1)
        return FLOAT_LEN_ERROR; 
 
    // floating_point_number element check
    if (number_characters(floating_point_number, '.', floating_point_number_len) > 1 ||\
    number_characters(floating_point_number, '.', floating_point_number_len) < 1)
        return CHARACTER_ERROR;
    if (number_characters(floating_point_number, 'E', floating_point_number_len) > 1 ||\
    number_characters(floating_point_number, 'E', floating_point_number_len) < 1)
        return CHARACTER_ERROR;
    if (number_characters(floating_point_number, '+', floating_point_number_len) + \
    number_characters(floating_point_number, '-', floating_point_number_len) > 2 ||\
    number_characters(floating_point_number, '+', floating_point_number_len) + \
    number_characters(floating_point_number, '-', floating_point_number_len) < 2)
        return CHARACTER_ERROR;
 
    // mantissa length check
    int mantissa_len = exp_index - 2;
    if (mantissa_len > MANTISSA_MAX_LEN)
        return MANTISSA_LEN_ERROR;
    if (mantissa_len < MANTISSA_MIN_LEN)
        return MANTISSA_LEN_ERROR;
 
    // order check
    int order_len = floating_point_number_len - exp_index - 3;
    if (order_len > ORDER_MAX_LEN)
        return ORDER_LEN_ERROR;
    if (order_len < ORDER_MIN_LEN)
        return ORDER_LEN_ERROR;
 
    // integer_number check + character location check             MY EXAMPLE: +0.64E-10
    if (floating_point_number[0] != '+' && floating_point_number[0] != '-')
        return CHARACTER_LOCATION_ERROR;
    if (number_check(floating_point_number, 1, point_index) != OK)
        return NUMBER_CHECK_ERORR; // +23432.
    if (number_check(floating_point_number, point_index + 1, exp_index) != OK)
        return NUMBER_CHECK_ERORR; // .24234E
    if (floating_point_number[exp_index + 1] != '+' && floating_point_number[exp_index + 1] != '-')
        return CHARACTER_LOCATION_ERROR;
    if (number_check(floating_point_number, exp_index + 2, floating_point_number_len - 1) != OK)
        return NUMBER_CHECK_ERORR; // E+234
 
    // the extra zeros check
    if (floating_point_number[1] == '0' && point_index != 2)
        return EXTRA_ZEROS_ERROR;
    if (floating_point_number[exp_index - 1] == '0' && mantissa_len != point_index)
        return EXTRA_ZEROS_ERROR;
    if (floating_point_number[exp_index + 2] == '0' && order_len != 1)
        return EXTRA_ZEROS_ERROR;
 
    // division by zero check
    if (mantissa_len == 2  && floating_point_number[point_index - 1] == '0'\
    && floating_point_number[point_index + 1] == '0')
        return DIVISION_BY_ZERO_ERROR;
    if (mantissa_len == 1 && (floating_point_number[point_index - 1] == '0' || floating_point_number[point_index + 1] == '0'))
        return DIVISION_BY_ZERO_ERROR;
 
    return OK;
}
 
int main(void)
{
    int test;
    char integer_number[INT_LEN] = { '\0' };
    char floating_point_number[FLOAT_LEN] = { '\0' };

    print_invite();
    test = condition_test(integer_number, floating_point_number);
    if (test != OK)
    {
        print_error(test);
        return test;
    }
 
    structure_filling(floating_point_number);
    create_integer_number();
    if (division_two_numbers(integer_number) == NULL_PRINT)
        return OK;
    test = normalized_output();
    if (test != OK)
    {
        print_error(test);
        return test;
    }
 
    return OK;
}

