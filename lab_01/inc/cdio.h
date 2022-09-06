#ifndef CDIO_H
#define CDIO_H

#include "const.h"

// Ввод числа
int input_number(struct number *number);

// Вывод числа
void print_number(struct number number);

// Вывод примера
void print_multiply(struct number num1, struct number num2, struct number result);

#endif // CDIO_H
