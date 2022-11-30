#include <stdio.h>
#include "graph_matrix.h"

#include "cdio.h"

// Поиск в глубину
int dfs(graph_t graph, int prev)
{
    int res;

    if (prev == graph.node_B)
        return 1;

    if (graph.visited[prev - 1])
        return 0;

    graph.visited[prev - 1] = 1;

    for (int j = 0; j < graph.n; j++)
        if (graph.matrix[prev - 1][j] == 1 && graph.visited[j] == 0)
        {
            res = dfs(graph, j + 1);

            if (res)
                return 1;
        }

    return 0;
}

// Удаляем граф (матрица)
void graph_init(graph_t *graph)
{
    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
            graph->matrix[i][j] = 0;
        graph->visited[i] = 0;
    }

    graph->node_A = 0;
    graph->node_B = 0;
    graph->n = 0;
}

// Нахождение существующих дорог
static roads_t count_roads(graph_t *graph)
{
    roads_t roads;
    roads.n = 0;

    for (int i = 0; i < graph->n - 1; i++)
        for (int j = i + 1; j < graph->n; j++)
            if (graph->matrix[i][j] == 1)
            {
                roads.rows[roads.n] = i;
                roads.columns[roads.n] = j;
                roads.n++;
            }

    return roads;
}

// Удаление из графа трех конкретных дорог
static void delete_three_rodes(graph_t *dst_graph, roads_t roads, graph_t src_graph, int ind_1, int ind_2, int ind_3)
{
    dst_graph->n = src_graph.n;
    dst_graph->node_A = src_graph.node_A;
    dst_graph->node_B = src_graph.node_B;

    for (int i = 0; i < roads.n; i++)
        if (i != ind_1 && i != ind_2 && i != ind_3)
        {
            dst_graph->matrix[roads.rows[i]][roads.columns[i]] = 1;
            dst_graph->matrix[roads.columns[i]][roads.rows[i]] = 1;
        }
}

// Функция, позволяющая узнать, можно ли убрать 3 любые дороги так, чтобы из города А
// нельзя было попасть в город B  (mode = 1 - убрать вывод результата работы функции)
void process(graph_t graph, int mode)
{
    graph_t tmp;
    roads_t roads = count_roads(&graph);
    int res;

    if (graph.node_A == graph.node_B && mode == 0)
    {
        print_result(roads, 0, 0, 0);
        return;
    }
    else if (graph.node_A == graph.node_B)
        return;

    for (int i = 0; i < roads.n - 2; i++)
        for (int j = i + 1; j < roads.n - 1; j++)
            for (int k = j + 1; k < roads.n; k++)
            {
                graph_init(&tmp);
                delete_three_rodes(&tmp, roads, graph, i, j, k);
                res = dfs(tmp, tmp.node_A);

                if (res == 0 && mode == 0)
                {
                    print_result(roads, i, j, k);
                    export_to_dot(&tmp, "del_graph.gv");
                    return;
                }
                else if (res == 0)
                    return;
            }

    if (mode == 0)
        print_result(roads, 0, 0, 0);
}

// Экспорт графа в DOT формат
void export_to_dot(graph_t *graph, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    char flag = 0;

    fprintf(file, "graph graph_test {\n");

    for (int i = 0; i < graph->n - 1; i++)
    {
        flag = 0;

        for (int j = i + 1; j < graph->n; j++)
            if (graph->matrix[i][j] == 1)
            {
                fprintf(file, "%d -- %d;\n", i + 1, j + 1);
                flag = 1;
            }

        if (!flag)
            fprintf(file, "%d;\n", i + 1);

    }

    fprintf(file, "}\n");
    fclose(file);
}


