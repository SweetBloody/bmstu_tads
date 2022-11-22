#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include "cdio.h"
#include "process.h"
#include "time_analysis.h"
#include "structs.h"

#define N 1000

// Анализ обычного умножения
double time_analysis(matrix_t matrix, vector_t vector)
{
    clock_t start, stop;
    double time = 0;

    for (int i = 0; i < N; i++)
    {
        start = clock();
        multiply_vector_matrix(vector, matrix);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Анализ разреженного умножения
double time_analysis_sparse(matrix_s_t matrix_s, vector_s_t vector_s)
{
    clock_t start, stop;
    double time = 0;

    for (int i = 0; i < N; i++)
    {
        start = clock();
        sparse_multiply_vector_matrix(vector_s, matrix_s);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Анализ времени и памяти
void analysis()
{
    double time1, time2;
    int matrix_N, matrix_M, vector_len;
    matrix_t matrix;
    matrix_s_t matrix_s;
    vector_t vector;
    vector_s_t vector_s;

    input_data_for_analysis(&matrix_N, &matrix_M, &vector_len);

    printf("|-----|-----------------------------|-----------------------------|\n");
    printf("|     |            time             |        memory (matrix)      |\n");
    printf("|     |--------------|--------------|--------------|--------------|\n");
    printf("|     |   standart   |    sparse    |   standart   |    sparse    |\n");
    printf("|-----|--------------|--------------|--------------|--------------|\n");


    for (int i = 0; i <= 100; i += 10)
    {
        random_matrix(&matrix, matrix_N, matrix_M, i);
        random_vector(&vector, vector_len, i);

        matrix_s = get_sparse_matrix(matrix);
        vector_s = get_sparse_vector(vector);

        time1 = time_analysis(matrix, vector);
        time2 = time_analysis_sparse(matrix_s, vector_s);

        printf("| %3d |   %8.0lf   |    %6.0lf    |   %8ld   |    %6ld    |\n",
               i, time1, time2, sizeof(matrix.data[0][0]) * matrix.rows * matrix.columns,
               (sizeof(matrix_s.data[0]) + sizeof(matrix_s.strings[0])) * matrix_s.pointer[matrix_s.columns] + sizeof(matrix_s.pointer[0]) * (matrix_s.columns + 1));
        printf("|-----|--------------|--------------|--------------|--------------|\n");
    }
}