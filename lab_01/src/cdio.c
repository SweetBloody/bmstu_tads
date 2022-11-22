#include "const.h"

// Ввод числа
int input_number(struct number *number)
{
    char in_str[42], int_tmp_part[2 * MAX_MANTISSA], dec_tmp_part[2 * MAX_MANTISSA], exp_tmp[MAX_EXP];
    int index = 0, index_int_tmp = 0, index_dec_tmp = 0, index_exp_tmp = 0;
    char *ch;

    printf("  |                              | (tip: 30 figures for mantissa)\n");
    ch = fgets(in_str, 42, stdin);

    if (ch == NULL)
        return INCORRECT_INPUT;

    if (in_str[0] == '\n')
        return EMPTY_STRING;

    if (in_str[strlen(in_str) - 1] == '\n')
        in_str[strlen(in_str) - 1] = '\0';

    if (strlen(in_str) > 40)
        return NUMBER_INPUT_OVERFLOW;

    // Проверка знака мантиссы
    if (in_str[0] == '-' || in_str[0] == '+')
    {
        index += 1;
        number->mantis_sign = in_str[0];
    }
    else
        number->mantis_sign = '+';

    // Анализ символов до точки
    if (in_str[index] != '0' && in_str[index] != '.')
    {
        while (isdigit((int) in_str[index]))
        {
            int_tmp_part[index_int_tmp] = in_str[index];
            index += 1;
            index_int_tmp += 1;
        }

        if (index_int_tmp > MAX_MANTISSA)
            return 1;

        if (in_str[index] == '.')
            index += 1;
    }
    else if (in_str[index] == '0')
    {
        while (in_str[index] == '0')
            index += 1;

        if (in_str[index] == '.')
            index += 1;
    }
    else if (in_str[index] == '.')
        index += 1;
    else
        return INCORRECT_INPUT;

    // Анализ символов после точки
    if (in_str[index] == '\0')
    {
        to_norm_number(number, int_tmp_part, index_int_tmp, dec_tmp_part, index_dec_tmp, exp_tmp, index_exp_tmp);
        return 0;
    }
    else if (isdigit((int) in_str[index]))
    {
        while (isdigit((int) in_str[index]))
        {
            dec_tmp_part[index_dec_tmp] = in_str[index];
            index += 1;
            index_dec_tmp += 1;
        }

        if (index_dec_tmp > MAX_MANTISSA)
            return NUMBER_INPUT_OVERFLOW;
    }


    // Анализ символов после десятичных знаков
    if (in_str[index] == '\0')
    {
        number->exp_sign = '+';
        to_norm_number(number, int_tmp_part, index_int_tmp, dec_tmp_part, index_dec_tmp, exp_tmp, index_exp_tmp);
        return 0;
    }
    else if (in_str[index] == 'E' || in_str[index] == 'e')
        index += 1;
    else
        return INCORRECT_INPUT;

    // Проверка знака порядка
    if (isspace((int) in_str[index]) || isalpha((int) in_str[index]))
        return INCORRECT_INPUT;
    else if (in_str[index] == '-' || in_str[index] == '+')
    {
        number->exp_sign = in_str[index];
        index += 1;
    }
    else
        number->exp_sign = '+';

    if (isspace((int) in_str[index]) || isalpha((int) in_str[index]))
        return INCORRECT_INPUT;

    // Анализ порядка
    while (isdigit((int) in_str[index]))
    {
        exp_tmp[index_exp_tmp] = in_str[index];
        index += 1;
        index_exp_tmp += 1;

        if (isspace((int) in_str[index]) || isalpha((int) in_str[index]))
            return INCORRECT_INPUT;
    }

    if (index_exp_tmp > MAX_EXP)
        return EXP_INPUT_OVERFLOW;

    to_norm_number(number, int_tmp_part, index_int_tmp, dec_tmp_part, index_dec_tmp, exp_tmp, index_exp_tmp);

    return 0;
}

// Вывод числа
void print_number(struct number number)
{
    printf("%c0.", number.mantis_sign);

    for (int i = 0; i < number.mantissa_num; i++)
        printf("%d", number.mantissa[i]);

    printf("E%c%d\n", number.exp_sign, number.exp);

}

// Вывод примера
void print_multiply(struct number num1, struct number num2, struct number result)
{
    printf("Result of multiply:\n  ");
    print_number(num1);
    printf("*\n  ");
    print_number(num2);
    printf("-------------------------------------\n");
    print_number(result);
}
