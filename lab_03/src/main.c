#include <stdio.h>
#include "cdio.h"
#include "const.h"
#include "file_process.h"
#include "process.h"
#include "structs.h"
#include "time_analysis.h"

int main(int argc, char **argv)
{
    int ch, choice = -1;
    matrix_t matrix;
    matrix_t matrix_res;
    vector_t vector;
    matrix_s_t matrix_s;
    matrix_s_t matrix_s_res;
    vector_s_t vector_s;

    if (argc != 3)
    {
        print_errors(INCORRECT_ARGS);
        return INCORRECT_ARGS;
    }

    ch = file_check(argv[1]);

    if (ch != OK)
    {
        print_errors(ch);
        return ch;
    }

    ch = file_check(argv[2]);

    if (ch != OK)
    {
        print_errors(ch);
        return ch;
    }

    vector.len = -1;
    matrix.rows = -1;

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                ch = input_matrix_from_file(argv[1], &matrix, vector.len);

                if (ch == INCORRECT_INPUT)
                {
                    print_errors(ch);
                    return ch;
                }

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                    matrix_s = get_sparse_matrix(matrix);
                break;

            case 2:
                ch = input_matrix_randomly(&matrix, vector.len);

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                {
                    print_matrix(matrix);
                    matrix_s = get_sparse_matrix(matrix);
                }
                break;

            case 3:
                ch = input_matrix_manually(&matrix, vector.len);

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                {
                    print_matrix(matrix);
                    matrix_s = get_sparse_matrix(matrix);
                }
                break;

            case 4:
                ch = input_vector_from_file(argv[2], &vector, matrix.rows);

                if (ch == INCORRECT_INPUT)
                {
                    print_errors(ch);
                    return ch;
                }

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                    vector_s = get_sparse_vector(vector);
                break;

            case 5:
                ch = input_vector_randomly(&vector, matrix.rows);

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                {
                    print_vector(vector);
                    vector_s = get_sparse_vector(vector);
                }
                break;

            case 6:
                ch = input_vector_manually(&vector, matrix.rows);

                if (ch == IMPOSSIBLE_TO_MULTIPLY)
                    printf("It will be impossible to multiply vector and matrix"
                           "with such matrix size!\n");
                else
                {
                    print_vector(vector);
                    vector_s = get_sparse_vector(vector);
                }
                break;

            case 7:
                matrix_res = multiply_vector_matrix(vector, matrix);
                print_matrix(matrix_res);
                matrix_s_res = get_sparse_matrix(matrix_res);
                break;

            case 8:
                matrix_s_res = sparse_multiply_vector_matrix(vector_s, matrix_s);
                print_sparse_matrix(matrix_s_res);
                matrix_res = get_simple_matrix(matrix_s_res);
                break;

            case 9:
                print_matrix(matrix);
                print_sparse_matrix(matrix_s);
                break;

            case 10:
                print_vector(vector);
                print_sparse_vector(vector_s);
                break;

            case 11:
                print_matrix(matrix_res);
                break;

            case 12:
                print_sparse_matrix(matrix_s_res);
                break;

            case 13:
                analysis();
                break;

            case 14:
                delete_matrix(&matrix);
                break;

            case 15:
                delete_vector(&vector);
                break;
        }
    }

    return OK;
}