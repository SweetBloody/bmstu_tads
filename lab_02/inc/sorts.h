#ifndef LAB_02_SORTS_H
#define LAB_02_SORTS_H

#include "../inc/structs.h"

// Компаратор theatre_name
int compare_theatre_name(const void *el_1, const void *el_2);

// Компаратор play_name
int compare_play_name(const void *el_1, const void *el_2);

// Компаратор price
int compare_price(const void *el_1, const void *el_2);

// Компаратор theatre_name для массива key
int compare_key_theatre_name(const void *el_1, const void *el_2);

// Компаратор play_name для массива key
int compare_key_play_name(const void *el_1, const void *el_2);

// Компаратор play_name для массива key
int compare_key_price(const void *el_1, const void *el_2);

// Сортировка всего изначального массива (пузырьком)
void sort_array(struct theatre *array_theatre, int array_theatre_length, int (*comparator)(const void *, const void *));

// Сортировка массива ключей (пузырьком)
void sort_key_array(struct key_theatre *array_theatre, int array_theatre_length, int (*comparator)(const void *, const void *));

// Сортировка всей таблицы по ключу
void sort_initial_array_by_keys(struct theatre *array_theatre, int array_theatre_length);

// Сортировка массива ключей
int sort_key_array_by_keys(struct theatre *array_theatre, struct key_theatre *key_theatre_array, int array_theatre_length);

#endif //LAB_02_SORTS_H
