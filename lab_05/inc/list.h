#ifndef LAB_05_STRUCTS_H
#define LAB_05_STRUCTS_H

typedef struct list_queue_tt list_queue_t;

// Очередь в виде списка
struct list_queue_tt
{
    char type;
    list_queue_t *next;
};

// Добавление элемента в очерель (список)
void add_to_list_queue(list_queue_t **pin, char type);

// Удаление элемента из очереди (список)
int delete_from_list_queue(list_queue_t **pin, list_queue_t **pout);

// Очистка списка
void free_list(list_queue_t **pin, list_queue_t **pout);

#endif //LAB_05_STRUCTS_H
