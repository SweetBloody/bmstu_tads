#ifndef PROCESS_H
#define PROCESS_H

#include "const.h"

// Перевод char в int
int chars_to_num(char chars[], int index);

// Умножение мантисс
int multiply(struct number num1, struct number num2, int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA], int *total_mant_length);

// Суммируем числа после умножения
int sum_multi_numbers(int mul_numbers[MAX_MANTISSA][3 * MAX_MANTISSA], int result_mantissa[3 * MAX_MANTISSA], int sum_length, int sum_amount);

// Реверс массива с мантиссой после сложения чисел, полученных после умножения
void reverse_result_mantissa(int result_mantissa[3 * MAX_MANTISSA], int length);

// Собираем результат в структуру
int build_result(struct number *result_num, struct number num1, struct number num2,
                  int mantissa[3 * MAX_MANTISSA], int result_mantissa_length, int total_mant_length, int zero_count);

#endif // PROCESS_H
