#ifndef LAB_03_CDIO_H
#define LAB_03_CDIO_H

#include "structs.h"

// Заполнение матрицы нулями
void make_null_matrix(matrix_t *matrix);

// Заполнение матрицы
int input_matrix_from_file(char *file_name, matrix_t *matrix, int vector_len);

// Заполнение матрицы рандомно
int input_matrix_randomly(matrix_t *matrix, int vector_len);

// Заполнение матрицы вручную
int input_matrix_manually(matrix_t *matrix, int vector_len);

// Ввод вектора из файла
int input_vector_from_file(char *file_name, vector_t *vector, int matrix_rows);

// Заполнение вектора рандомно
int input_vector_randomly(vector_t *vector, int matrix_rows);

// Заполнение вектора вручную
int input_vector_manually(vector_t *vector, int matrix_rows);

// Удаление матрицы
void delete_matrix(matrix_t *matrix);

// Удаление вектора
void delete_vector(vector_t *vector);

// Вывод обычной матрицы
void print_matrix(matrix_t matrix);

// Вывод разреженной матрицы
void print_sparse_matrix(matrix_s_t matrix_s);

// Вывод обычного вектора
void print_vector(vector_t vector);

// Вывод разреженного вектора
void print_sparse_vector(vector_s_t vector_s);

// Вывод меню
int print_menu();

// Вывод сообщений об ошибках
void print_errors(int ch);

// Ввод размерности для анализа
void input_data_for_analysis(int *matrix_n, int *matrix_m, int *vector_len);

// Создание рандомной матрицы для анализа
int random_matrix(matrix_t *matrix, int n, int m, double percentage);

// Создание рандомной вектор для анализа
int random_vector(vector_t *vector, int n, double percentage);

#endif //LAB_03_CDIO_H
