#ifndef LAB_05_ARRAY_H
#define LAB_05_ARRAY_H

#include "const.h"

// Очередь в виде массива
typedef struct
{
    char data[MAX_QUEUE_LEN];
    char *pointer;
    char *start;
    char *end;
} array_queue_t;

// Инициализация очереди массивом
void init_array_queue(array_queue_t *array_queue);

// Добавление элемента в очерель (массив)
int add_to_array_queue(array_queue_t *array_queue, char type);

// Удаление элемента из очереди (массив)
int delete_from_array_queue(array_queue_t *array_queue);

#endif //LAB_05_ARRAY_H
