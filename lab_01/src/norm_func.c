#include "const.h"

//  Создаем нормализированную структуру
void to_norm_number(struct number *number, char int_tmp_part[2 * MAX_MANTISSA], int index_int_tmp,
                   char dec_tmp_part[2 * MAX_MANTISSA], int index_dec_tmp,
                   char exp_tmp[MAX_EXP], int index_exp_tmp)
{
    int exp_number = chars_to_num(exp_tmp, index_exp_tmp), zero_number = 0;

    if (number->exp_sign == '-')
        exp_number = -exp_number;

    // Нормализируем дробную часть
    if (index_int_tmp == 0)
    {
        for (int i = 0; i < index_dec_tmp; i++)
        {
            if (dec_tmp_part[i] == '0')
                zero_number += 1;
            else
                break;
        }
        if (zero_number)
            for (int i = 0; i < index_dec_tmp - zero_number; i++)
                dec_tmp_part[i] = dec_tmp_part[i + zero_number];

        index_dec_tmp -= zero_number;
        exp_number -= zero_number;
    }

    // Нормализируем целую часть
    if (index_int_tmp)
    {
        for (int i = index_dec_tmp + index_int_tmp; i >= index_int_tmp; i--)
            dec_tmp_part[i] = dec_tmp_part[i - index_int_tmp];

        for (int i = 0; i < index_int_tmp; i++)
            dec_tmp_part[i] = int_tmp_part[i];
    }

    exp_number += index_int_tmp;

    //  Сохраняем нормализированные данные в структуру
    for (int i = 0; i < index_dec_tmp + index_int_tmp; i++)
        number->mantissa[i] = dec_tmp_part[i] - '0';

    number->mantissa_num = index_dec_tmp + index_int_tmp;

    if (exp_number >= 0)
        number->exp_sign = '+';
    else
    {
        number->exp_sign = '-';
        exp_number = -exp_number;
    }

    number->exp = exp_number;
}

// Приводим числа после умножения к одной длине
int norm_mul_numbers(int sum_amount, int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA])
{
    int max_len = 0, len = 0, j = 0;
    for (int i = 0; i < sum_amount; i++)
    {
        len = 0;
        j = 0;

        while (mul_numbers[i][j] != -1)
        {
            len += 1;
            j += 1;
        }

        if (len > max_len)
            max_len = len;
    }

    for (int i = 0; i < sum_amount; i++)
        for (j = 0; j < max_len; j++)
            if (mul_numbers[i][j] == -1)
            {
                mul_numbers[i][j] = 0;
                mul_numbers[i][j + 1] = -1;
            }

    return max_len;
}

// Нормализируем мантиссу результата
int norm_result_mantissa(int num_array[3 * MAX_MANTISSA], int length)
{
    int index, zero_count = 0;

    if (length > MAX_MANTISSA)
    {
        if (num_array[MAX_MANTISSA] >= 5)
            num_array[MAX_MANTISSA - 1] += 1;

        if (num_array[MAX_MANTISSA - 1] >= 10)
            index = MAX_MANTISSA - 1;

        while (num_array[index] >= 10)
        {
            num_array[index - 1] += num_array[index] / 10;
            num_array[index] %= 10;
            index -= 1;
        }

        length = MAX_MANTISSA;
    }

    index = length - 1;
    while (num_array[index] == 0 && index != 0)
    {
        zero_count += 1;
        index -= 1;
    }

    return zero_count;
}
