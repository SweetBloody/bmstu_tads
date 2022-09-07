#include "process.h"
#include "structs.h"
#include "cdio.h"

// Получение разреженной матрицы из обычной
matrix_s_t get_sparse_matrix(matrix_t matrix)
{
    matrix_s_t matrix_s;
    int non_null_index = 0, col_index = 0;

    matrix_s.pointer[col_index] = 0;

    for (int j = 0; j < matrix.columns; j++)
    {
        col_index += 1;
        matrix_s.pointer[col_index] = matrix_s.pointer[col_index - 1];

        for (int i = 0; i < matrix.rows; i++)
            if (matrix.data[i][j] != 0)
            {
                matrix_s.pointer[col_index] += 1;
                matrix_s.data[non_null_index] = matrix.data[i][j];
                matrix_s.strings[non_null_index] = i;
                non_null_index += 1;
            }
    }

    matrix_s.rows = matrix.rows;
    matrix_s.columns = matrix.columns;

    return matrix_s;
}

// Получение обычной матрицы из разреженной
matrix_t get_simple_matrix(matrix_s_t matrix_s)
{
    matrix_t matrix;
    int index = 0;

    matrix.rows = matrix_s.rows;
    matrix.columns = matrix_s.columns;

    make_null_matrix(&matrix);

    for (int j = 0; j < matrix.columns; j++)
        for (int i = 0; i < matrix_s.pointer[j + 1] - matrix_s.pointer[j]; i++)
        {
            matrix.data[matrix_s.strings[index]][j] = matrix_s.data[index];
            index += 1;
        }

    return matrix;
}

// Получение разреженного вектора из обычного
vector_s_t get_sparse_vector(vector_t vector)
{
    vector_s_t vector_s;
    int non_null_index = 0, pointer_index = 0;

    vector_s.pointer[pointer_index] = 0;

    for (int i = 0; i < vector.len; i++)
    {
        pointer_index += 1;
        vector_s.pointer[pointer_index] = vector_s.pointer[pointer_index - 1];

        if (vector.data[i] != 0)
        {
            vector_s.data[non_null_index] = vector.data[i];
            vector_s.columns[non_null_index] = i;
            vector_s.pointer[pointer_index] += 1;
            non_null_index += 1;
        }
    }

    vector_s.len = vector.len;

    return vector_s;
}

// Умножение матрицы на вектор в стандартном виде
matrix_t multiply_vector_matrix(vector_t vector, matrix_t matrix)
{
    int sum;
    matrix_t matrix_res;

    matrix_res.rows = 1;
    matrix_res.columns = matrix.columns;

    for (int i = 0; i < matrix_res.columns; i++)
    {
        sum = 0;

        for (int j = 0; j < vector.len; j++)
            sum += vector.data[j] * matrix.data[j][i];

        matrix_res.data[0][i] = sum;
    }

    return matrix_res;
}

// Умножение матрицы на вектор в разреженном виде
matrix_s_t sparse_multiply_vector_matrix(vector_s_t vector_s, matrix_s_t matrix_s)
{
    matrix_s_t matrix_res;
    int sum, index_pointer = 0, index_data = 0;

    matrix_res.pointer[index_pointer] = 0;

    for (int i = 0; i < matrix_s.columns; i++)
    {
        sum = 0;

        index_pointer += 1;
        matrix_res.pointer[index_pointer] = matrix_res.pointer[index_pointer - 1];

        for (int j = matrix_s.pointer[i]; j < matrix_s.pointer[i + 1]; j++)
            if (matrix_s.strings[j] == vector_s.columns[vector_s.pointer[matrix_s.strings[j]]])
                sum += matrix_s.data[j] * vector_s.data[vector_s.pointer[matrix_s.strings[j]]];

        if (sum != 0)
            {
                matrix_res.data[index_data] = sum;
                matrix_res.strings[index_data] = 0;
                matrix_res.pointer[index_pointer] += 1;
                index_data += 1;
            }
    }

    matrix_res.columns = matrix_s.columns;
    matrix_res.rows = 1;

    return matrix_res;
}