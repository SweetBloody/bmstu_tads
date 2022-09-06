#ifndef LAB_02_CDIO_H
#define LAB_02_CDIO_H

#include <stdio.h>
#include "../inc/structs.h"

// Ввод структуры theatre
int input_theatre(FILE *file, struct theatre *theatre);

// Ввод массива структур theatre
int input_array_of_theatre(char *file_name, struct theatre *array_theatre, int *array_theatre_length);

// Вывод данных о структуре theatre
void print_theatre_info(struct theatre theatre, int num);

// Вывод массива структур theatre
void print_array_of_theatre(struct theatre *array_theatre, int array_theatre_length);

// Вывод массива структур key_theatre (ключей)
void print_key_array(struct key_theatre *array_theatre, int array_theatre_length, int key);

// Вывод меню
int print_menu();

// Меню для сортировки исходной таблицы
int sort_menu();

// Вывод массива в отсортированном виде с помощью массива ключей
void print_key_sorted_array(struct theatre *array_theatre, struct key_theatre *key_theatre, int array_theatre_length, int key);

// Ввод параметров поиска мюзикла
void input_find_parameters(int *age, int *max_duration);

// Ввод параметров удаления
int input_delete_parameters(int *number, char *string);

// Вывод таблицы значений времени
void print_time_table(double time_1, double time_2, double time_3, double time_4);

// Вывод различий во времени
void print_time_analysis(int percent_1, int percent_2, int min, int max);

// Вывод значений памяти
void print_memory_table(struct theatre *array_theatre, struct key_theatre *array_key_theatre, int length);

// Вывод различий в памяти
void print_memory_analysis(int percent_1, int percent_2);

// Вывод сообщений об ошибках
void print_errors(int ch);

#endif //LAB_02_CDIO_H
