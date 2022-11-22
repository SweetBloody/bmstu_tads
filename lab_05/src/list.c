#include <stdlib.h>
#include "list.h"
#include "const.h"

// Добавление элемента в очерель (список)
void add_to_list_queue(list_queue_t **pin, char type)
{
    list_queue_t *new_elem;

    new_elem = (list_queue_t *) malloc(sizeof(list_queue_t));

    if (new_elem)
    {
        new_elem->type = type;
        new_elem->next = (*pin);
        (*pin) = new_elem;
    }
}

// Удаление элемента из очереди (список)
int delete_from_list_queue(list_queue_t **pin, list_queue_t **pout)
{
    list_queue_t *cur = *pin;

    if (cur == *pout)
    {
        free(*pout);
        *pout = NULL;
        *pin = NULL;
        return QUEUE_EMPTY;
    }

    while (cur->next != *pout)
        cur = cur->next;

    free(*pout);
    *pout = cur;
    (*pout)->next = NULL;

    return OK;
}

// Очистка списка
void free_list(list_queue_t **pin, list_queue_t **pout)
{
    while (*pout != *pin)
        delete_from_list_queue(pin, pout);

    if (*pin != NULL && *pout != NULL)
        delete_from_list_queue(pin, pout);
}