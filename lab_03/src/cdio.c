#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "const.h"
#include "cdio.h"

// Заполнение матрицы из файла
int input_matrix_from_file(char *file_name, matrix_t *matrix, int vector_len)
{
    int ch, n, m;
    FILE *file = fopen(file_name, "r");

    ch = fscanf(file, "%d %d", &n, &m);

    if (ch != 2 || n > MAX_MATRIX_SIZE || m > MAX_MATRIX_SIZE || n <= 0 || m <= 0)
    {
        fclose(file);
        return INCORRECT_INPUT;
    }

    if (n != vector_len && vector_len != -1)
    {
        fclose(file);
        return IMPOSSIBLE_TO_MULTIPLY;
    }

    matrix->rows = n;
    matrix->columns = m;
    ch = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ch += fscanf(file, "%d", &matrix->data[i][j]);

    fclose(file);

    if (ch != n * m)
        return INCORRECT_INPUT;

    return OK;
}

// Заполнение матрицы нулями
void make_null_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            matrix->data[i][j] = 0;
}

// Заполнение матрицы рандомно
int input_matrix_randomly(matrix_t *matrix, int vector_len)
{
    int ch, n, m, k = 0, amount, flag;
    double percentage;
    srand(1);

    ch = 0;
    while (ch != 2 || n > MAX_MATRIX_SIZE || m > MAX_MATRIX_SIZE || n <= 0 || m <= 0)
    {
        printf("Input the size of matrix (rows and columns):\n");
        ch = scanf("%d%d", &n, &m);
    }

    if (n != vector_len && vector_len != -1)
        return IMPOSSIBLE_TO_MULTIPLY;

    matrix->rows = n;
    matrix->columns = m;

    make_null_matrix(matrix);

    ch = 0;
    while (ch != 1 || percentage < 0 || percentage > 100)
    {
        printf("Input the percentage of matrix filling (with non-null elems):\n");
        ch = scanf("%lf", &percentage);
    }

    amount = (int) round(percentage / 100 * n * m);

    while (k < amount)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                flag = rand() % 4;

                if (flag == 1 && matrix->data[i][j] == 0)
                {
                    ch = rand() % 100 - 50;

                    while (ch == 0)
                        ch = rand() % 100 - 50;

                    matrix->data[i][j] = ch;
                    k += 1;

                    if (k == amount)
                        return OK;
                }
            }
    }

    return OK;
}

// Заполнение матрицы вручную
int input_matrix_manually(matrix_t *matrix, int vector_len)
{
    int ch = 0, number, n, m, amount;

    while (ch != 2 || n > MAX_MATRIX_SIZE || m > MAX_MATRIX_SIZE || n <= 0 || m <= 0)
    {
        printf("Input the size of matrix (rows and columns):\n");
        ch = scanf("%d%d", &n, &m);
    }

    if (n != vector_len && vector_len != -1)
        return IMPOSSIBLE_TO_MULTIPLY;

    matrix->rows = n;
    matrix->columns = m;

    make_null_matrix(matrix);

    ch = 0;
    while (ch != 1 || amount > n * m || amount <= 0)
    {
        printf("Input the amount of non-null elements:\n");
        ch = scanf("%d", &amount);
    }

    printf("Input the coords and the value of non-null elements:\n");

    for (int k = 0; k < amount; k++)
    {
        ch = 0;
        while (ch != 3 || n < 0 || n > matrix->rows || m < 0 || m > matrix->columns)
        {
            printf("#%d\n", k + 1);
            ch = scanf("%d%d%d", &n, &m, &number);
        }

        matrix->data[n - 1][m - 1] = number;
    }

    return OK;
}

// Ввод вектора из файла
int input_vector_from_file(char *file_name, vector_t *vector, int matrix_rows)
{
    int ch, n;
    FILE *file = fopen(file_name, "r");

    ch = fscanf(file, "%d", &n);

    if (ch != 1 || n > MAX_MATRIX_SIZE || n <= 0)
    {
        fclose(file);
        return INCORRECT_INPUT;
    }

    if (n != matrix_rows && matrix_rows != -1)
    {
        fclose(file);
        return IMPOSSIBLE_TO_MULTIPLY;
    }

    vector->len = n;
    ch = 0;

    for (int i = 0; i < n; i++)
        ch += fscanf(file, "%d", &vector->data[i]);

    fclose(file);

    if (ch != n)
        return INCORRECT_INPUT;

    return OK;
}

// Заполнение вектора нулями
void make_null_vector(vector_t *vector)
{
    for (int i = 0; i < vector->len; i++)
        vector->data[i] = 0;
}

// Заполнение вектора рандомно
int input_vector_randomly(vector_t *vector, int matrix_rows)
{
    int ch, n, k = 0, amount, flag;
    double percentage;
    srand(1);

    ch = 0;
    while (ch != 1 || n > MAX_MATRIX_SIZE || n <= 0)
    {
        printf("Input the size of vector:\n");
        ch = scanf("%d", &n);
    }

    if (n != matrix_rows && matrix_rows != -1)
        return IMPOSSIBLE_TO_MULTIPLY;

    vector->len = n;

    make_null_vector(vector);

    ch = 0;
    while (ch != 1 || percentage < 0 || percentage > 100)
    {
        printf("Input the percentage of vector filling (with non-null elems):\n");
        ch = scanf("%lf", &percentage);
    }

    amount = (int) round(percentage / 100 * n);

    while (k < amount)
    {
        for (int i = 0; i < n; i++)
        {
            flag = rand() % 4;

            if (flag == 1 && vector->data[i] == 0)
            {
                ch = rand() % 100 - 50;

                while (ch == 0)
                    ch = rand() % 100 - 50;

                vector->data[i] = ch;
                k += 1;

                if (k == amount)
                    return OK;
            }
        }
    }

    return OK;
}

// Заполнение вектора вручную
int input_vector_manually(vector_t *vector, int matrix_rows)
{
    int ch = 0, number, n, amount;

    while (ch != 2 || n > MAX_MATRIX_SIZE || n <= 0)
    {
        printf("Input the size of vector:\n");
        ch = scanf("%d", &n);
    }

    if (n != matrix_rows && matrix_rows != -1)
        return IMPOSSIBLE_TO_MULTIPLY;

    vector->len = n;

    make_null_vector(vector);

    ch = 0;
    while (ch != 1 || amount > n || amount <= 0)
    {
        printf("Input the amount of non-null elements:\n");
        ch = scanf("%d", &amount);
    }

    printf("Input the index and the value of non-null elements:\n");

    for (int k = 0; k < amount; k++)
    {
        ch = 0;
        while (ch != 3 || n < 0 || n > vector->len)
        {
            printf("#%d\n", k + 1);
            ch = scanf("%d%d", &n, &number);
        }

        vector->data[n - 1] = number;
    }

    return OK;
}

// Удаление матрицы
void delete_matrix(matrix_t *matrix)
{
    make_null_matrix(matrix);
    matrix->rows = -1;
}

// Удаление вектора
void delete_vector(vector_t *vector)
{
    make_null_vector(vector);
    vector->len = -1;
}

// Вывод обычной матрицы
void print_matrix(matrix_t matrix)
{
    printf("Matrix:\n");

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
            printf("%4d ", matrix.data[i][j]);

        printf("\n");
    }

    printf("\n");
}

// Вывод разреженной матрицы
void print_sparse_matrix(matrix_s_t matrix_s)
{
    printf("Sparse matrix:\n");

    printf("Data:    ");
    for (int i = 0; i < matrix_s.pointer[matrix_s.columns]; i++)
        printf("%4d", matrix_s.data[i]);
    printf("\n");

    printf("Strings: ");
    for (int i = 0; i < matrix_s.pointer[matrix_s.columns]; i++)
        printf("%4d", matrix_s.strings[i]);
    printf("\n");

    printf("Pointer: ");
    for (int i = 0; i < matrix_s.columns + 1; i++)
        printf("%4d", matrix_s.pointer[i]);
    printf("\n\n");
}

// Вывод обычного вектора
void print_vector(vector_t vector)
{
    printf("Vector:\n");

    for (int i = 0; i < vector.len; i++)
        printf("%4d", vector.data[i]);

    printf("\n");
}

// Вывод разреженного вектора
void print_sparse_vector(vector_s_t vector_s)
{
    printf("Sparse vector:\n");

    printf("Data:    ");
    for (int i = 0; i < vector_s.pointer[vector_s.len]; i++)
        printf("%4d", vector_s.data[i]);
    printf("\n");

    printf("Columns: ");
    for (int i = 0; i < vector_s.pointer[vector_s.len]; i++)
        printf("%4d", vector_s.columns[i]);
    printf("\n");

    printf("Pointer: ");
    for (int i = 0; i < vector_s.len + 1; i++)
        printf("%4d", vector_s.pointer[i]);
    printf("\n\n");
}

// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|--------------------------------------------|\n");
    printf("| MENU:                                      |\n");
    printf("|  1 - input matrix from file;               |\n");
    printf("|  2 - input matrix randomly;                |\n");
    printf("|  3 - input matrix manually;                |\n");
    printf("|  4 - input vector from file;               |\n");
    printf("|  5 - input vector randomly;                |\n");
    printf("|  6 - input vector manually;                |\n");
    printf("|  7 - multiplication of matrix              |\n"
                  "|         and vector in standart format;     |\n");
    printf("|  8 - multiplication of matrix              |\n"
                  "|         and vector in sparse format;       |\n");
    printf("|  9 - print matrix;                         |\n");
    printf("| 10 - print vector;                         |\n");
    printf("| 11 - print result in standart format;      |\n");
    printf("| 12 - print result in sparse format;        |\n");
    printf("| 13 - results of time and memory analysis;  |\n");
    printf("| 14 - delete matrix;                        |\n");
    printf("| 15 - delete vector;                        |\n");
    printf("|  0 - exit;                                 |\n");
    printf("|--------------------------------------------|\n");
    printf("Your choice (from 0 to 15):\n");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    while (ch != 1 || number < 0 || number > 15)
    {
        printf("Please enter numbers from 0 to 15:\n");
        ch = scanf("%d", &number);
        scanf("%c", &n);
    }

    return number;
}

// Вывод сообщений об ошибках
void print_errors(int ch)
{
    if (ch == INCORRECT_ARGS)
        printf("INCORRECT_ARGS\n");

    if (ch == FILE_OPEN_ERR)
        printf("FILE_OPEN_ERR\n");

    if (ch == FILE_CLOSE_ERR)
        printf("FILE_CLOSE_ERR\n");

    if (ch == FILE_ERR)
        printf("FILE_ERR\n");

    if (ch == EMPTY_FILE)
        printf("EMPTY_FILE\n");

    if (ch == INCORRECT_INPUT)
        printf("INCORRECT_INPUT\n");
}

// Ввод размерности для анализа
void input_data_for_analysis(int *matrix_n, int *matrix_m, int *vector_len)
{
    int ch = 0;

    while (ch != 3 || *matrix_n <= 0 || *matrix_n > MAX_MATRIX_SIZE ||
            *matrix_m <= 0 || *matrix_m > MAX_MATRIX_SIZE ||
            *vector_len <= 0 || *vector_len > MAX_MATRIX_SIZE || *vector_len != *matrix_n)
    {
        printf("Input the matrix size (rows and columns) and the length of vector:\n");
        ch = scanf("%d%d%d", matrix_n, matrix_m, vector_len);
    }
}

// Создание рандомной матрицы для анализа
int random_matrix(matrix_t *matrix, int n, int m, double percentage)
{
    int ch, k = 0, amount, flag;
    srand(1);

    matrix->rows = n;
    matrix->columns = m;

    make_null_matrix(matrix);

    amount = (int) round(percentage / 100 * n * m);

    while (k < amount)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                flag = rand() % 4;

                if (flag == 1 && matrix->data[i][j] == 0)
                {
                    ch = rand() % 100 - 50;

                    while (ch == 0)
                        ch = rand() % 100 - 50;

                    matrix->data[i][j] = ch;
                    k += 1;

                    if (k == amount)
                        return OK;
                }
            }
    }

    return OK;
}

// Создание рандомной вектор для анализа
int random_vector(vector_t *vector, int n, double percentage)
{
    int ch, k = 0, amount, flag;

    vector->len = n;

    make_null_vector(vector);

    amount = (int) round(percentage / 100 * n);

    while (k < amount)
    {
        for (int i = 0; i < n; i++)
        {
            flag = rand() % 4;

            if (flag == 1 && vector->data[i] == 0)
            {
                ch = rand() % 100 - 50;

                while (ch == 0)
                    ch = rand() % 100 - 50;

                vector->data[i] = ch;
                k += 1;

                if (k == amount)
                    return OK;
            }
        }
    }

    return OK;
}