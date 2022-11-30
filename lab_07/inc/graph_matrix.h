#ifndef LAB_07_GRAPH_MATRIX_H
#define LAB_07_GRAPH_MATRIX_H

#include "const.h"

// Структура представления графа в виде матрицы
typedef struct
{
    int matrix[MAX][MAX];  // Матрица смежности
    int n;                 // Количество городов
    int node_A;            // Город отправления
    int node_B;            // Город назначения
    int visited[MAX];      // Массив посещенных городов
} graph_t;

// Структура сохранения существующих дорог
typedef struct
{
    int rows[MAX];         // Индекс города А
    int columns[MAX];      // Индекс города B (соответствующего городу А)
    int n;                 // Количество дорог
} roads_t;

// Поиск в глубину
int dfs(graph_t graph, int prev);

// Удаляем граф (матрица)
void graph_init(graph_t *graph);

// Функция, позволяющая узнать, можно ли убрать 3 любые дороги так, чтобы из города А
// нельзя было попасть в город B
void process(graph_t graph, int mode);

// Экспорт графа в DOT формат
void export_to_dot(graph_t *graph, char *file_name);

#endif //LAB_07_GRAPH_MATRIX_H
