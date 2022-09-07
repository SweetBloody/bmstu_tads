#ifndef LAB_03_PROCESS_H
#define LAB_03_PROCESS_H

#include "structs.h"

// Получение разреженной матрицы из обычной
matrix_s_t get_sparse_matrix(matrix_t matrix);

// Получение обычной матрицы из разреженной
matrix_t get_simple_matrix(matrix_s_t matrix_s);

// Получение разреженного вектора из обычного
vector_s_t get_sparse_vector(vector_t vector);

// Умножение матрицы на вектор в стандартном виде
matrix_t multiply_vector_matrix(vector_t vector, matrix_t matrix);

// Умножение матрицы на вектор в стандартном виде
matrix_s_t sparse_multiply_vector_matrix(vector_s_t vector_s, matrix_s_t matrix);

#endif //LAB_03_PROCESS_H
