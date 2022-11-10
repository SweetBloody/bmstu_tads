#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cdio.h"
#include "structs.h"

// Добавление элемента в стек (список)
int add_to_list_stack(struct list_stack_t **pointer, int *len, int number)
{
    struct list_stack_t *new_elem;

    if (*len + 1 > MAX_STACK_LEN)
        return STACK_OVERFLOW;

    new_elem = init_list_stack(number);

    new_elem->prev = *pointer;
    *len += 1;
    (*pointer) = new_elem;

    return OK;
}

// Удаление элемента из списка (список)
int delete_from_list_stack(struct list_stack_t **pointer, struct mem_array_t *mem_array)
{
    struct list_stack_t *cur = *pointer;

    if (cur->prev == NULL)
    {
        mem_array->data[mem_array->index] = (*pointer);
        mem_array->index += 1;
        free(*pointer);
        return STACK_EMPTY;
    }

    mem_array->data[mem_array->index] = (*pointer);
    mem_array->index += 1;
    cur = (*pointer)->prev;
    free(*pointer);
    *pointer = cur;

    return OK;
}

//// Поиск предыдущего элемента стека
//struct list_stack_t *find_prev_list(struct list_stack_t *list_stack, struct list_stack_t *pointer)
//{
//    struct list_stack_t *cur = list_stack;
//
//    if (cur == pointer)
//        return NULL;
//
//    while (cur->next != pointer)
//        cur = cur->next;
//
//    return cur;
//}

// Вывод убывающих последовательностей в обратном порядке (список)
void process_list_stack(struct list_stack_t **pointer, struct mem_array_t *mem_array)
{
    int begin_flag = 0, flag = 0, number;

    while ((*pointer)->prev != NULL)
    {
        number = (*pointer)->number;
        delete_from_list_stack(pointer, mem_array);

        if ((*pointer)->number > number)
        {
            if (begin_flag == 0)
            {
                printf ("Decreasing lists in stack (list):\n");
                begin_flag = 1;
            }

            flag = 1;
            printf("%4d", number);
        }
        else if (flag == 1 && (*pointer)->number < number)
        {
            printf("%4d\n", number);
            flag = 0;
        }
    }

    if (flag == 1)
        printf("%4d\n", (*pointer)->number);

    delete_from_list_stack(pointer, mem_array);

    if (begin_flag == 0)
        printf("There are no decreasing lists in stack (list)!\n");
}

//// Вывод убывающих последовательностей в обратном порядке (список)
//void incorrect_process_list_stack(struct list_stack_t *list_stack, struct list_stack_t *pointer)
//{
//    int flag = 0;
//    struct list_stack_t *prev = find_prev_list(list_stack, pointer);
//
//    while (pointer != list_stack)
//    {
//        if (pointer->number < prev->number)
//        {
//            if (flag == 0)
//            {
//                printf ("Decreasing lists in stack (list):\n");
//                flag = 1;
//            }
//
//            printf("%4d", pointer->number);
//        }
//        else if (pointer->next != NULL && pointer->number > pointer->next->number)
//            printf("%4d\n", pointer->number);
//
//        pointer = prev;
//
//        if (pointer != list_stack)
//            prev = find_prev_list(list_stack, pointer);
//    }
//
//    if (pointer->next != NULL && pointer->number > pointer->next->number)
//        printf("%4d\n", pointer->number);
//
//    if (flag == 0)
//        printf("There are no decreasing lists in stack (list)!\n");
//}

// Добавление элемента в стек (массив)
int add_to_array_stack(array_stack_t *array_stack, int number)
{
    if (array_stack->pointer + 1 == array_stack->end)
        return STACK_OVERFLOW;

    array_stack->pointer += 1;

    *array_stack->pointer = number;

    return OK;
}

// Удаление элемента из стека (массив)
int delete_from_array_stack(array_stack_t *array_stack)
{
    *array_stack->pointer = 0;
    array_stack->pointer -= 1;

    if (array_stack->pointer < array_stack->start)
        return STACK_EMPTY;

    return OK;
}

// Поиск предыдущего элемента стека
int *find_prev_array(array_stack_t array_stack, int *pa)
{
    int *cur = array_stack.start;

    if (cur == pa)
        return NULL;

    while (cur + 1 != pa)
        cur += 1;

    return cur;
}

// Вывод убывающих последовательностей в обратном порядке (массив)
void process_array_stack(array_stack_t *array_stack)
{
    int begin_flag = 0, flag = 0, number;

    while (array_stack->pointer != array_stack->start)
    {
        number = *array_stack->pointer;
        delete_from_array_stack(array_stack);

        if (*array_stack->pointer > number)
        {
            if (begin_flag == 0)
            {
                printf ("Decreasing lists in stack (array):\n");
                begin_flag = 1;
            }

            flag = 1;
            printf("%4d", number);
        }
        else if (flag == 1 && *array_stack->pointer < number)
        {
            printf("%4d\n", number);
            flag = 0;
        }
    }

    if (flag == 1)
        printf("%4d\n", *array_stack->pointer);

    delete_from_array_stack(array_stack);

    if (begin_flag == 0)
        printf("There are no decreasing lists in stack (array)!\n");
}

// Вывод убывающих последовательностей в обратном порядке (массив)
void incorrect_process_array_stack(array_stack_t array_stack)
{
    int *pa = array_stack.pointer, flag = 0;
    int *prev = find_prev_array(array_stack, pa);

    while (pa != array_stack.start)
    {
        if (*pa < *prev)
        {
            if (flag == 0)
            {
                printf ("Decreasing lists in stack (array):\n");
                flag = 1;
            }

            printf("%4d", *pa);
        }
        else if (pa != array_stack.pointer && *pa > *(pa + 1))
            printf("%4d\n", *pa);

        pa = prev;

        if (pa != array_stack.data)
            prev = find_prev_array(array_stack, pa);
    }

    if (pa != array_stack.pointer && *pa > *(pa + 1))
        printf("%4d\n", *pa);

    if (flag == 0)
        printf("There are no decreasing lists in stack (array)!\n");
}

// (некорректный) Вывод убывающих последовательностей в обратном порядке (массив)
void incorrect2_process_array_stack(array_stack_t array_stack)
{
    int *pa = array_stack.pointer, flag = 0;

    while (pa != array_stack.start)
    {
        if (*pa < *(pa - 1))
        {
            if (flag == 0)
            {
                printf ("Decreasing lists in stack (array):\n");
                flag = 1;
            }

            printf("%4d", *pa);
        }
        else if (pa != array_stack.pointer && *pa > *(pa + 1))
            printf("%4d\n", *pa);

        pa -= 1;
    }

    if (pa != array_stack.pointer && *pa > *(pa + 1))
        printf("%4d\n", *pa);

    if (flag == 0)
        printf("There are no decreasing lists in stack (array)!\n");
}