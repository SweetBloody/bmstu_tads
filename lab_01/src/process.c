#include "const.h"

// Перевод char в int
int chars_to_num(char chars[], int index)
{
    int number = 0, count = index;

    for (int i = 0; i < index; i++)
        number += (chars[i] - '0') * pow(10, count - i - 1);

    return number;
}

// Умножение мантисс
int multiply(struct number num1, struct number num2, int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA], int *total_mant_length)
{
    int k, p = 0, q = 0, tmp_num, in_mind = 0, len = 0;
    struct number tmp_number;

    *total_mant_length = num1.mantissa_num + num2.mantissa_num;

    if (num2.mantissa_num > num1.mantissa_num)
    {
        tmp_number = num1;
        num1 = num2;
        num2 = tmp_number;
    }

    for (int i = num2.mantissa_num - 1; i >= 0; i--)
    {
        in_mind = 0;
        q = 0;

        for (k = 0; k < len; k++)
            mul_numbers[p][k] = 0;

        for (int j = num1.mantissa_num - 1; j >= 0; j--)
        {
            tmp_num = num2.mantissa[i] * num1.mantissa[j] + in_mind;

            in_mind = tmp_num / 10;
            tmp_num %= 10;

            mul_numbers[p][q + k] = tmp_num;
            q += 1;
        }

        if (in_mind > 0)
        {
            mul_numbers[p][q + k] = in_mind;
            q += 1;
        }
        mul_numbers[p][q + k] = -1;

        len += 1;
        p += 1;
    }

    return num2.mantissa_num;
}

// Суммируем числа после умножения
int sum_multi_numbers(int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA], int result_mantissa[3 * MAX_MANTISSA], int sum_length, int sum_amount)
{
    int tmp_num = 0, in_mind = 0, i;


    for (i = 0; i < sum_length; i++)
    {
        tmp_num = 0;

        for (int j = 0; j < sum_amount; j++)
            tmp_num += mul_numbers[j][i];

        tmp_num += in_mind;
        in_mind = tmp_num / 10;
        tmp_num %= 10;

        result_mantissa[i] = tmp_num;
    }

    if (in_mind > 0)
    {
        result_mantissa[i] = in_mind;
        i += 1;
    }

    return i;
}

// Реверс массива с мантиссой после сложения чисел, полученных после умножения
void reverse_result_mantissa(int result_mantissa[3 * MAX_MANTISSA], int length)
{
    int tmp;

    for (int i = 0; i < length / 2; i++)
    {
        tmp = result_mantissa[i];
        result_mantissa[i] = result_mantissa[length - 1 - i];
        result_mantissa[length - 1 - i] = tmp;
    }
}

// Собираем результат в структуру
int build_result(struct number *result_num, struct number num1, struct number num2,
                  int mantissa[3 * MAX_MANTISSA], int result_mantissa_length, int total_mant_length, int zero_count)
{
    int exp1, exp2, result_exp, delta = 0, flag = 0;


    if ((num1.mantis_sign == '+' && num2.mantis_sign == '-') || (num1.mantis_sign == '-' && num2.mantis_sign == '+'))
        result_num->mantis_sign = '-';
    else
        result_num->mantis_sign = '+';

    for (int i = 0; i < result_mantissa_length; i++)
    {
        result_num->mantissa[i] = mantissa[i];
    }

    if (result_mantissa_length > MAX_MANTISSA)
        result_num->mantissa_num = MAX_MANTISSA - zero_count;
    else
        result_num->mantissa_num = result_mantissa_length - zero_count;

    exp1 = num1.exp;
    exp2 = num2.exp;

    if (num1.exp_sign == '-')
        exp1 = -exp1;

    if (num2.exp_sign == '-')
        exp2 = -exp2;

    delta = total_mant_length - result_mantissa_length;

    result_exp = exp1 + exp2 - delta;

    if (result_exp < 0)
        result_num->exp_sign = '-';
    else
        result_num->exp_sign = '+';

    if (result_num->mantissa_num == 0)
    {
        result_num->exp = 0;
        result_num->mantissa[0] = 0;
        result_num->mantissa_num = 1;
    }
    else
        result_num->exp = abs(result_exp);

    if (result_num->exp > 99999)
        flag = 1;

    return flag;
}
