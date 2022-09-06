#ifndef NORM_FUNC_H
#define NORM_FUNC_H

#include "const.h"
#define MAX_EXP 5
#define MAX_MANTISSA 30

//  Создаем нормализированную структуру
void to_norm_number(struct number *number, char int_tmp_part[2 * MAX_MANTISSA], int index_int_tmp,
                   char dec_tmp_part[2 * MAX_MANTISSA], int index_dec_tmp,
                   char exp_tmp[MAX_EXP], int index_exp_tmp);

// Приводим числа после умножения к одной длине
int norm_mul_numbers(int sum_amount, int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA]);

// Нормализируем мантиссу результата
int norm_result_mantissa(int num_array[3 * MAX_MANTISSA], int length);

#endif // NORM_FUNC_H
