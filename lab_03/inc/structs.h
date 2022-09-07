#ifndef LAB_03_STRUCTS_H
#define LAB_03_STRUCTS_H

#include "const.h"

// Вектор в стандартном виде
typedef struct
{
    int len;
    int data[MAX_MATRIX_SIZE];
} vector_t;

// Вектор в разреженном виде
typedef struct
{
    int len;
    int data[MAX_MATRIX_SIZE];        // Массив ненулевых элементов
    int columns[MAX_MATRIX_SIZE];     // Номера столбцов ненулевых элементов
    int pointer[MAX_MATRIX_SIZE + 1];
} vector_s_t;

// Матрица в стандартном виде
typedef struct
{
    int rows;
    int columns;
    int data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} matrix_t;

// Матрица в разреженном виде
typedef struct
{
    int rows;
    int columns;
    int data[MAX_MATRIX_ELEMS];       // Массив ненулевых элементов
    int strings[MAX_MATRIX_ELEMS];    // Номера строк ненулевых элементов
    int pointer[MAX_MATRIX_SIZE + 1]; // Количество ненулевых элементов от каждого столбца до нулевого
} matrix_s_t;

#endif //LAB_03_STRUCTS_H
