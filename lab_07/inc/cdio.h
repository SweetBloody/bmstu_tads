#ifndef LAB_07_CDIO_H
#define LAB_07_CDIO_H

#include "graph_matrix.h"

// Проверка файла
int file_check(char *file_name, char *mode);

// Ввод данных о графе (о ребрах) - матрица
void input_graph(graph_t *graph);

// Ввод данных о графе (о ребрах) из файла
int input_graph_from_file(graph_t *graph);

// Ввод двух городов для удаления 3 дорог между ними
void input_nodes(graph_t *graph);

// Вывод матрицы графа
void print_graph(graph_t graph);

// Вывод сообщения о результате обработки графа
void print_result(roads_t roads, int ind_1, int ind_2, int ind_3);

// Вывод меню
int print_menu();

#endif //LAB_07_CDIO_H
