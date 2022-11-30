#include <stdio.h>
#include "cdio.h"

// Проверка файла
int file_check(char *file_name, char *mode)
{
    FILE *f = fopen(file_name, mode);

    if (f == NULL)
        return FILE_OPEN_ERR;

    if (ferror(f) != 0)
        return FILE_ERR;

    if (fclose(f) == EOF)
        return FILE_CLOSE_ERR;

    return OK;
}

// Ввод данных о графе (о ребрах)
void input_graph(graph_t *graph)
{
    int ch = 0, number = 0, col;

    while (ch != 1 || number <= 0)
    {
        setbuf(stdin, NULL);
        printf("Input number of nodes:\n");
        ch = scanf("%d", &number);
    }

    graph->n = number;
    printf("Input connections (to end input -1)\n");

    for (int i = 0; i < graph->n; i++)
    {
        number = 0;
        col = 0;
        printf("Input number of nodes that connected with node %d:\n", i + 1);

        while (number != -1 && col != graph->n)
        {
            ch = 0;
            setbuf(stdin, NULL);
            ch = scanf("%d", &number);

            if (ch != 1 || (number <= 0 && number != -1) || number > graph->n)
            {
                number = -1;
                i--;
            }

            if (number != -1)
            {
                graph->matrix[i][number - 1] = 1;
                graph->matrix[number - 1][i] = 1;
                col++;
            }
        }

        graph->visited[i] = 0;
    }
}

// Ввод данных о графе (о ребрах) из файла
int input_graph_from_file(graph_t *graph)
{
    int ch = 0, number = 0, col;
    FILE *file = fopen("data.txt", "r");

    ch = fscanf(file, "%d", &number);

    if (ch != 1 || number <= 0)
        return INCORRECT_INPUT;

    graph->n = number;

    for (int i = 0; i < graph->n; i++)
    {
        number = 0;
        col = 0;

        while (number != -1 && col != graph->n)
        {
            ch = fscanf(file, "%d", &number);

            if (ch != 1 || (number <= 0 && number != -1) || number > graph->n)
                return INCORRECT_INPUT;

            if (number != -1)
            {
                graph->matrix[i][number - 1] = 1;
                graph->matrix[number - 1][i] = 1;
                col++;
            }
        }

        graph->visited[i] = 0;
    }

    return OK;
}

// Ввод двух городов для удаления 3 дорог между ними
void input_nodes(graph_t *graph)
{
    int ch = 0;
    int number = 0;

    while (ch != 1 || number <= 0 || number > graph->n)
    {
        setbuf(stdin, NULL);
        printf("Input number of A node:\n");
        ch = scanf("%d", &number);
    }

    graph->node_A = number;
    ch = 0;
    number = 0;

    while (ch != 1 || number <= 0 || number > graph->n)
    {
        setbuf(stdin, NULL);
        printf("Input number of B node:\n");
        ch = scanf("%d", &number);
    }

    graph->node_B = number;
}

// Вывод матрицы графа
void print_graph(graph_t graph)
{
    printf("Graph matrix:\n");
    for (int i = 0; i < graph.n; i++)
    {
        if (i == 0)
        {
            printf("    ");
            for (int j = 0; j < graph.n; j++)
                printf("%4d ", j + 1);
            printf("\n    ");
            for (int j = 0; j < graph.n; j++)
                printf("-----");
            printf("\n");
        }


        for (int j = 0; j < graph.n; j++)
        {
            if (j == 0)
                printf("%2d |", i + 1);

            printf("%4d ", graph.matrix[i][j]);
        }

        printf("\n");
    }
}

// Вывод сообщения о результате обработки графа
void print_result(roads_t roads, int ind_1, int ind_2, int ind_3)
{
    if (ind_1 == 0 && ind_2 == 0 && ind_3 == 0)
        printf("Cannot find 3 roads to delete.\n");
    else
    {
        printf("You need to delete these 3 roads:\n");
        printf("%d -- %d\n", roads.rows[ind_1] + 1, roads.columns[ind_1] + 1);
        printf("%d -- %d\n", roads.rows[ind_2] + 1, roads.columns[ind_2] + 1);
        printf("%d -- %d\n", roads.rows[ind_3] + 1, roads.columns[ind_3] + 1);
    }
}


// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|-------------------------------------------------|\n");
    printf("| MENU:                                           |\n");
    printf("|  1 - input graph;                               |\n");
    printf("|  2 - input graph from file;                     |\n");
    printf("|  3 - draw graph;                                |\n");
    printf("|  4 - choose two nodes for task;                 |\n");
    printf("|  5 - delete 3 rodes;                            |\n");
    printf("|  6 - analysis;                                  |\n");
    printf("|  0 - exit;                                      |\n");
    printf("|-------------------------------------------------|\n");
    printf(">");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    while (ch != 1 || number < 0 || number > 6)
    {
        printf("Please enter numbers from 0 to 6!\n>");
        ch = scanf("%d", &number);
        scanf("%c", &n);
    }

    return number;
}