#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>
#include "analysis.h"

#define N 1000
#define M 10

// Замер времени поиска в глубину
static int64_t time_analysis_dfs_matrix(graph_t graph, int node_A, int node_B)
{
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time = 0;

    graph.node_A = node_A;
    graph.node_B = node_B;

    for (int i = 0; i < N; i++)
    {
        gettimeofday(&tv_start, NULL);
        dfs(graph, graph.node_A);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL\
                        + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    return elapsed_time / N;
}

// Замер времени работы функции process
static int64_t time_analysis_process(graph_t graph, int node_A, int node_B)
{
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time = 0;

    graph.node_A = node_A;
    graph.node_B = node_B;

    for (int i = 0; i < M; i++)
    {
        gettimeofday(&tv_start, NULL);
        process(graph, 1);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL\
                        + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    return elapsed_time / M;
}

// Отрисовка таблицы
static void print_table(graph_t graph, int64_t (*time_func)(graph_t, int, int), char *msg)
{
    int64_t time;

    printf("        %s", msg);
    printf("\n|======|");
    for (int j = 0; j < graph.n; j++)
        printf("=======|");
    printf("\n");

    for (int i = 0; i < graph.n; i++)
    {
        printf("|  A/B |");
        for (int j = 0; j < graph.n; j++)
            printf("%6d |", j + 1);
        printf("\n|------|");
        for (int j = 0; j < graph.n; j++)
            printf("-------|");
        printf("\n|  %2d  |", i + 1);
        for (int j = 0; j < graph.n; j++)
        {
            time = time_func(graph, i + 1, j + 1);
            printf("%6d |", (int) time);
        }
        printf("\n|======|");
        for (int j = 0; j < graph.n; j++)
            printf("=======|");
        printf("\n");
    }
}

// Анализ времени работы алгоритмов графов
void analysis(graph_t graph)
{
    print_table(graph, time_analysis_dfs_matrix, "TIME OF DFS");
    print_table(graph, time_analysis_process, "TIME OF FINDING ROADS TO DELETE");

    printf("Memory for matrix: %ld\n", sizeof(int) * MAX);
}