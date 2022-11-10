#ifndef LAB_04_STRUCTS_H
#define LAB_04_STRUCTS_H

#include "const.h"

// Стек в виде массиве
typedef struct
{
    int data[MAX_STACK_LEN];
    int *pointer;
    int *start;
    int *end;
} array_stack_t;

// Стек в виде списка
struct list_stack_t
{
    int number;
    struct list_stack_t *prev;
};

struct mem_array_t
{
    int index;
    struct list_stack_t *data[MAX_STACK_LEN];
};

#endif //LAB_04_STRUCTS_H
