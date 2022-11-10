#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "analysis.h"
#include "process.h"
#include "cdio.h"
#include "structs.h"

#define N 1000

// Удаление элемента из списка для анализа процесса(список)
int delete_from_list_stack_an(struct list_stack_t **pointer)
{
    struct list_stack_t *cur = *pointer;

    if (cur->prev == NULL)
    {
        free(*pointer);
        return STACK_EMPTY;
    }

    cur = (*pointer)->prev;
    free(*pointer);
    *pointer = cur;

    return OK;
}

// Анализ убывающих последовательностей в обратном порядке (список)
int analysis_process_list_stack(struct list_stack_t **pointer)
{
    int begin_flag = 0, flag = 0, number, n;

    while ((*pointer)->prev != NULL)
    {
        number = (*pointer)->number;
        delete_from_list_stack_an(pointer);

        if ((*pointer)->number > number)
        {
            if (begin_flag == 0)
                begin_flag = 1;

            flag = 1;
            n = number;
        }
        else if (flag == 1 && (*pointer)->number < number)
        {
            n = number;
            flag = 0;
        }
    }

    if (flag == 1)
        n = (*pointer)->number;

    delete_from_list_stack_an(pointer);

    if (begin_flag == 0)
        printf("There are no decreasing lists in stack (list)!\n");

    return n;
}

// Анализ убывающих последовательностей в обратном порядке (массив)
int analysis_process_array_stack(array_stack_t *array_stack)
{
    int begin_flag = 0, flag = 0, number, n;

    while (array_stack->pointer != array_stack->start)
    {
        number = *array_stack->pointer;
        delete_from_array_stack(array_stack);

        if (*array_stack->pointer > number)
        {
            if (begin_flag == 0)
                begin_flag = 1;

            flag = 1;
            n = number;
        }
        else if (flag == 1 && *array_stack->pointer < number)
        {
            n = number;
            flag = 0;
        }
    }

    if (flag == 1)
        n = *array_stack->pointer;

    delete_from_array_stack(array_stack);

    if (begin_flag == 0)
        printf("There are no decreasing lists in stack (array)!\n");

    return n;
}


// Заполнение стеков случайными числами
void fill_stacks(struct list_stack_t **list_stack, struct list_stack_t **pointer, array_stack_t *array_stack, int len)
{
    int flag = 0, number, n;

    srand(3);

    for (int i = 0; i < len; i++)
    {
        number = rand() % 100 - 50;

        // Заполнение списка
        if (flag == 0)
        {
            *list_stack = init_list_stack(number);
            *pointer = *list_stack;
            n = 1;
        }
        else
            add_to_list_stack(pointer, &n, number);

        flag = 1;

        // Заполнение массива
        add_to_array_stack(array_stack, number);
    }
}


void time_analysis(int len, double *time1, double *time2)
{
    array_stack_t array_stack;
    struct list_stack_t *list_stack = NULL;
    struct list_stack_t *pointer;
    clock_t start, stop;

    for (int i = 0; i < N; i++)
    {
        init_array_stack(&array_stack);
        fill_stacks(&list_stack, &pointer, &array_stack, len);

        start = clock();
        analysis_process_array_stack(&array_stack);
        stop = clock();
        *time1 += stop - start;

        start = clock();
        analysis_process_list_stack(&pointer);
        stop = clock();
        *time2 += stop - start;
    }

    *time1 = *time1 / N / CLOCKS_PER_SEC * 1000000;
    *time2 = *time2 / N / CLOCKS_PER_SEC * 1000000;
}

// Время добавления и удаления из стека списком
void time_list(double *time1, double *time2, int amount)
{
    struct list_stack_t *list_stack = NULL;
    struct list_stack_t *pointer;
    clock_t start, stop;
    int flag, n;

    for (int j = 0; j < N; j++)
    {
        flag  = 0;
        start = clock();
        for (int i = 0; i < amount; i++)
        {
            if (flag == 0)
            {
                list_stack = init_list_stack(i);
                pointer = list_stack;
                n = 1;
            }
            else
                add_to_list_stack(&pointer, &n, i);

            flag = 1;
        }
        stop = clock();
        *time1 += stop - start;

        start = clock();
        for (int i = 0; i < amount; i++)
        {
            delete_from_list_stack_an(&pointer);
            n -= 1;
        }
        stop = clock();
        *time2 += stop - start;
    }

    *time1 = *time1 / N / CLOCKS_PER_SEC * 1000000;
    *time2 = *time2 / N / CLOCKS_PER_SEC * 1000000;
}

// Время добавления и удаления из стека массивом
void time_array(double *time1, double *time2, int amount)
{
    array_stack_t array_stack;
    clock_t start, stop;

    init_array_stack(&array_stack);

    for (int j = 0; j < N; j++)
    {
        start = clock();
        for (int i = 0; i < amount; i++)
            add_to_array_stack(&array_stack, i);
        stop = clock();
        *time1 += stop - start;

        start = clock();
        for (int i = 0; i < amount; i++)
            delete_from_array_stack(&array_stack);
        stop = clock();
        *time2 += stop - start;
    }

    *time1 = *time1 / N / CLOCKS_PER_SEC * 1000000;
    *time2 = *time2 / N / CLOCKS_PER_SEC * 1000000;
}

// Анализ времени и памяти
void analysis()
{
    double time1, time2;
    array_stack_t array_stack;

    printf("|-----|-----------------------------|-----------------------------|\n");
    printf("|     |            time             |            memory           |\n");
    printf("|  N  |--------------|--------------|--------------|--------------|\n");
    printf("|     |     array    |     list     |     array    |     list     |\n");
    printf("|-----|--------------|--------------|--------------|--------------|\n");


    for (int i = 20; i <= 200; i += 10)
    {
        time_analysis(i, &time1, &time2);

        printf("| %3d |   %8.0lf   |    %6.0lf    |   %8ld   |    %6ld    |\n",
               i, time1, time2,
               sizeof(array_stack.data[0]) * MAX_STACK_LEN + sizeof(array_stack.pointer) + sizeof(array_stack.start) + sizeof(array_stack.end),
               sizeof(struct list_stack_t) * i);
        printf("|-----|--------------|--------------|--------------|--------------|\n");
    }
}


// Анализ добавления\удаления
void time_push_pop()
{
    double time1, time2, time3, time4;

    printf("|-----|-----------------------------|-----------------------------|\n");
    printf("|     |            list             |            array            |\n");
    printf("|  N  |--------------|--------------|--------------|--------------|\n");
    printf("|     |      add     |    delete    |      add     |    delete    |\n");
    printf("|-----|--------------|--------------|--------------|--------------|\n");

    for (int i = 10; i <= 200; i += 20)
    {
        time_list(&time1, &time2, i);
        time_array(&time3, &time4, i);
        printf("| %3d |   %8.0lf   |    %6.0lf    |   %8.0lf   |    %6.0lf    |\n",
               i, time1, time2, time3, time4);
        printf("|-----|--------------|--------------|--------------|--------------|\n");
    }
}

//// Анализ убывающих последовательностей в обратном порядке (список)
//int analysis_incorrect_process_list_stack(struct list_stack_t *list_stack, struct list_stack_t *pointer)
//{
//    int flag = 0, number;
//    struct list_stack_t *prev = find_prev_list(list_stack, pointer);
//
//    while (pointer != list_stack)
//    {
//        if (pointer->number < prev->number)
//        {
//            if (flag == 0)
//                flag = 1;
//
//            number = pointer->number;
//        }
//        else if (pointer->next != NULL && pointer->number > pointer->next->number)
//            number = pointer->number;
//
//        pointer = prev;
//
//        if (pointer != list_stack)
//            prev = find_prev_list(list_stack, pointer);
//    }
//
//    if (pointer->next != NULL && pointer->number > pointer->next->number)
//        number = pointer->number;
//
//    if (flag == 0)
//        number = 404;
//
//    return number;
//}
//
//
//// Анализ убывающих последовательностей в обратном порядке (массив)
//int analysis_incorrect_process_array_stack(array_stack_t array_stack)
//{
//    int *pa = array_stack.pointer, flag = 0, number;
//    int *prev = find_prev_array(array_stack, pa);
//
//    while (pa != array_stack.start)
//    {
//        if (*pa < *prev)
//        {
//            if (flag == 0)
//                flag = 1;
//
//            number = *pa;
//        }
//        else if (pa != array_stack.pointer && *pa > *(pa + 1))
//            number = *pa;
//
//        pa = prev;
//
//        if (pa != array_stack.data)
//            prev = find_prev_array(array_stack, pa);
//    }
//
//    if (pa != array_stack.pointer && *pa > *(pa + 1))
//        number = *pa;
//
//    if (flag == 0)
//        number = 404;
//
//    return number;
//}
//
//// Анализ обработки стека массивом
//double time_analysis_array(array_stack_t array_stack)
//{
//    clock_t start, stop;
//    double time = 0;
//
//    for (int i = 0; i < N; i++)
//    {
//        start = clock();
//        analysis_incorrect_process_array_stack(array_stack);
//        stop = clock();
//        time += stop - start;
//    }
//
//    return time / N / CLOCKS_PER_SEC * 1000000;
//}
//
//// Анализ обработаки стека списком
//double time_analysis_list(struct list_stack_t *list_stack, struct list_stack_t *pointer)
//{
//    clock_t start, stop;
//    double time = 0;
//
//    for (int i = 0; i < N; i++)
//    {
//        start = clock();
//        analysis_incorrect_process_list_stack(list_stack, pointer);
//        stop = clock();
//        time += stop - start;
//    }
//
//    return time / N / CLOCKS_PER_SEC * 1000000;
//}
//
//// Анализ времени и памяти
//void analysis()
//{
//    double time1, time2;
//    array_stack_t array_stack;
//    struct list_stack_t *list_stack = NULL;
//    struct list_stack_t *pointer;
//
//    printf("|-----|-----------------------------|-----------------------------|\n");
//    printf("|     |            time             |            memory           |\n");
//    printf("|  N  |--------------|--------------|--------------|--------------|\n");
//    printf("|     |     array    |     list     |     array    |     list     |\n");
//    printf("|-----|--------------|--------------|--------------|--------------|\n");
//
//
//    for (int i = 20; i <= 500; i += 20)
//    {
//        init_array_stack(&array_stack);
//        fill_stacks(&list_stack, &pointer, &array_stack, i);
//
//        time1 = time_analysis_array(array_stack);
//        time2 = time_analysis_list(list_stack, pointer);
//
//        printf("| %3d |   %8.0lf   |    %6.0lf    |   %8d   |    %6d    |\n",
//               i, time1, time2,
//               sizeof(array_stack.data[0]) * i + sizeof(array_stack.pointer) + sizeof(array_stack.start) + sizeof(array_stack.end),
//               sizeof(struct list_stack_t) * i);
//        printf("|-----|--------------|--------------|--------------|--------------|\n");
//    }
//}

//
//// (некорректный) Анализ убывающих последовательностей в обратном порядке (массив)
//int analysis_incorrect2_process_array_stack(array_stack_t array_stack)
//{
//    int *pa = array_stack.pointer, flag = 0, number;
//
//    while (pa != array_stack.start)
//    {
//        if (*pa < *(pa - 1))
//        {
//            if (flag == 0)
//                flag = 1;
//
//            number = *pa;
//        }
//        else if (pa != array_stack.pointer && *pa > *(pa + 1))
//            number = *pa;
//
//        pa -= 1;
//    }
//
//    if (pa != array_stack.pointer && *pa > *(pa + 1))
//        number = *pa;
//
//    if (flag == 0)
//        number = 404;
//
//    return number;
//}