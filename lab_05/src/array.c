#include "array.h"

// Инициализация очереди массивом
void init_array_queue(array_queue_t *array_queue)
{
    array_queue->pointer = array_queue->data - 1;
    array_queue->start = array_queue->data;
    array_queue->end = array_queue->start + MAX_QUEUE_LEN;
}

// Добавление элемента в очерель (массив)
int add_to_array_queue(array_queue_t *array_queue, char type)
{
    if (array_queue->pointer + 1 == array_queue->end)
        return QUEUE_OVERFLOW;

    array_queue->pointer += 1;
    *array_queue->pointer = type;

    return OK;
}

// Удаление элемента из очереди (массив)
int delete_from_array_queue(array_queue_t *array_queue)
{
    *array_queue->pointer = 0;
    array_queue->pointer -= 1;

    if (array_queue->pointer < array_queue->start)
        return QUEUE_EMPTY;

    return OK;
}
