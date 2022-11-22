#ifndef CONST_H
#define CONST_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "struct.h"
#include "cdio.h"
#include "norm_func.h"
#include "process.h"

#define MAX_EXP 5
#define MAX_MANTISSA 30

#define INCORRECT_INPUT 1 // Неверный ввод числа
#define NUMBER_INPUT_OVERFLOW 2 // Превышение максимальной длины мантиссы при вводе
#define EMPTY_STRING 3 // Пустая строка
#define EXP_INPUT_OVERFLOW 4 // Превышение максимальной длины порядка при вводе

#endif // CONST_H
