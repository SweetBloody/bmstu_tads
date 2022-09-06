#include "const.h"

int main()
{
    struct number num1, num2, result_num, tmp_num;
    int ch, mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA], result_mantissa[3 * MAX_MANTISSA],
            sum_length, sum_amount, result_mantissa_length, total_mant_length, zero_count;

    printf("This is a program that multiplies two float numbers.\n\n");
    printf("Use + or - before the number.\n");
    printf("Input 1st number:\n");
    ch = input_number(&num1);

    if (ch == INCORRECT_INPUT)
    {
        printf("INCORRECT_INPUT\n");
        return ch;
    }

    if (ch == NUMBER_INPUT_OVERFLOW)
    {
        printf("NUMBER_INPUT_OVERFLOW\n");
        return ch;
    }

    if (ch == EMPTY_STRING)
    {
        printf("EMPTY_STRING\n");
        return ch;
    }

    if (ch == EXP_INPUT_OVERFLOW)
    {
        printf("EXP_INPUT_OVERFLOW\n");
        return ch;
    }

    printf("Input 2nd number:\n");
    ch = input_number(&num2);

    if (ch == INCORRECT_INPUT)
    {
        printf("INCORRECT_INPUT\n");
        return ch;
    }

    if (ch == NUMBER_INPUT_OVERFLOW)
    {
        printf("NUMBER_INPUT_OVERFLOW\n");
        return ch;
    }

    if (ch == EMPTY_STRING)
    {
        printf("EMPTY_STRING\n");
        return ch;
    }

    if (ch == EXP_INPUT_OVERFLOW)
    {
        printf("EXP_INPUT_OVERFLOW\n");
        return ch;
    }
    tmp_num = num2;

    // Получаем числа после умножения мантисс
    sum_amount = multiply(num1, num2, mul_numbers, &total_mant_length);

    // Приводим эти числа к одной длине
    sum_length = norm_mul_numbers(sum_amount, mul_numbers);

    // Суммируем эти числа
    result_mantissa_length = sum_multi_numbers(mul_numbers, result_mantissa, sum_length, sum_amount);

    // Переворачиваем массив с результирующей мантиссой
    reverse_result_mantissa(result_mantissa, result_mantissa_length);

    // Нормализируем результирующую мантиссу
    zero_count = norm_result_mantissa(result_mantissa, result_mantissa_length);

    // Собираем результирующую структуру
    ch = build_result(&result_num, num1, num2, result_mantissa, result_mantissa_length, total_mant_length, zero_count);

    if (ch == 1)
    {
        printf("Incorrect result value!");
    }
    else
        print_multiply(num1, tmp_num, result_num);

    return 0;
}
