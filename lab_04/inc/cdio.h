#ifndef LAB_03_CDIO_H
#define LAB_03_CDIO_H

#include "structs.h"

// Ввод значения элемента
void input_number(int *number);

// Инициализация стека списком
struct list_stack_t *init_list_stack(int number);

// Вывод значений элементов стека (список)
void print_list_stack(struct list_stack_t *pointer, int len);

// Вывод адресов элементов стека (список)
void print_list_stack_address(struct list_stack_t *pointer, struct mem_array_t mem_array, int len);

// Инициализация стека массивом
void init_array_stack(array_stack_t *array_stack);

// Вывод стека (массив)
void print_array_stack(array_stack_t array_stack);

// Вывод меню
int print_menu();

#endif //LAB_03_CDIO_H
