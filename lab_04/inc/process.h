#ifndef LAB_04_PROCESS_H
#define LAB_04_PROCESS_H

#include "structs.h"

// Добавление элемента в стек (список)
int add_to_list_stack(struct list_stack_t **pointer, int *len, int number);

// Удаление элемента из списка (список)
int delete_from_list_stack(struct list_stack_t **pointer, struct mem_array_t *mem_array);

//// Поиск предыдущего элемента стека
//struct list_stack_t *find_prev_list(struct list_stack_t *list_stack, struct list_stack_t *pointer);

// Вывод убывающих последовательностей в обратном порядке (список)
void process_list_stack(struct list_stack_t **pointer, struct mem_array_t *mem_array);

//// Вывод убывающих последовательностей в обратном порядке (список)
//void incorrect_process_list_stack(struct list_stack_t *list_stack, struct list_stack_t *pointer);

// Добавление элемента в стек (массив)
int add_to_array_stack(array_stack_t *array_stack, int number);

// Удаление элемента из стека (массив)
int delete_from_array_stack(array_stack_t *array_stack);

// Поиск предыдущего элемента стека
int *find_prev_array(array_stack_t array_stack, int *pa);

// Вывод убывающих последовательностей в обратном порядке (массив)
void process_array_stack(array_stack_t *array_stack);

// Вывод убывающих последовательностей в обратном порядке (массив)
void incorrect_process_array_stack(array_stack_t array_stack);

// (некорректный) Вывод убывающих последовательностей в обратном порядке (массив)
void incorrect2_process_array_stack(array_stack_t array_stack);

#endif //LAB_04_PROCESS_H
