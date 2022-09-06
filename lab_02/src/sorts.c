#include <stdio.h>
#include <string.h>
#include "sorts.h"
#include "cdio.h"
#include "process.h"

// Компаратор theatre_name
int compare_theatre_name(const void *el_1, const void *el_2)
{
    struct theatre theatre_1 = *(struct theatre *) el_1;
    struct theatre theatre_2 = *(struct theatre *) el_2;

    return strcmp(theatre_1.theatre_name, theatre_2.theatre_name);
}

// Компаратор play_name
int compare_play_name(const void *el_1, const void *el_2)
{
    struct theatre theatre_1 = *(struct theatre *) el_1;
    struct theatre theatre_2 = *(struct theatre *) el_2;

    return strcmp(theatre_1.play_name, theatre_2.play_name);
}

// Компаратор price
int compare_price(const void *el_1, const void *el_2)
{
    struct theatre theatre_1 = *(struct theatre *) el_1;
    struct theatre theatre_2 = *(struct theatre *) el_2;
    int delta_1, delta_2;

    delta_1 = theatre_1.end_price - theatre_1.start_price;
    delta_2 = theatre_2.end_price - theatre_2.start_price;

    return delta_1 - delta_2;
}

//// Компаратор theatre_name для массива key
//int compare_key_theatre_name(const void *el_1, const void *el_2)
//{
//    struct key_theatre theatre_1 = *(struct key_theatre *) el_1;
//    struct key_theatre theatre_2 = *(struct key_theatre *) el_2;
//
//    return strcmp(theatre_1.theatre_name, theatre_2.theatre_name);
//}

// Компаратор play_name для массива key
int compare_key_play_name(const void *el_1, const void *el_2)
{
    struct key_theatre theatre_1 = *(struct key_theatre *) el_1;
    struct key_theatre theatre_2 = *(struct key_theatre *) el_2;

    return strcmp(theatre_1.play_name, theatre_2.play_name);
}

//// Компаратор play_name для массива key
//int compare_key_price(const void *el_1, const void *el_2)
//{
//    struct key_theatre theatre_1 = *(struct key_theatre *) el_1;
//    struct key_theatre theatre_2 = *(struct key_theatre *) el_2;
//
//    return theatre_1.delta - theatre_2.delta;
//}

// Сортировка всего изначального массива (пузырьком)
void sort_array(struct theatre *array_theatre, int array_theatre_length, int (*comparator)(const void *, const void *))
{
    struct theatre tmp_elem;
    int flag;

    for (int i = 0; i < array_theatre_length - 1; i++)
    {
        flag = 1;

        for (int j = 0; j < array_theatre_length - 1 - i; j++)
            if (comparator((void *) &array_theatre[j], (void *) &array_theatre[j + 1]) > 0)
            {
                tmp_elem = array_theatre[j];
                array_theatre[j] = array_theatre[j + 1];
                array_theatre[j + 1] = tmp_elem;
                flag = 0;
            }

        if (flag == 1)
            break;
    }
}

// Сортировка массива ключей (пузырьком)
void sort_key_array(struct key_theatre *array_theatre, int array_theatre_length, int (*comparator)(const void *, const void *))
{
    struct key_theatre tmp_elem;
    int flag;

    for (int i = 0; i < array_theatre_length - 1; i++)
    {
        flag = 1;

        for (int j = 0; j < array_theatre_length - 1 - i; j++)
            if (comparator((void *) &array_theatre[j], (void *) &array_theatre[j + 1]) > 0)
            {
                tmp_elem = array_theatre[j];
                array_theatre[j] = array_theatre[j + 1];
                array_theatre[j + 1] = tmp_elem;
                flag = 0;
            }

        if (flag == 1)
            break;
    }
}

// Сортировка всей таблицы по ключу
void sort_initial_array_by_keys(struct theatre *array_theatre, int array_theatre_length)
{
    int choice;

    choice = sort_menu();

    printf("Sorted initial array:\n");

    switch (choice)
    {
        case 1:
            sort_array(array_theatre, array_theatre_length, compare_theatre_name);
            break;
        case 2:
            sort_array(array_theatre, array_theatre_length, compare_play_name);
            break;
        case 3:
            sort_array(array_theatre, array_theatre_length, compare_price);
            break;
    }
}

// Сортировка массива ключей
int sort_key_array_by_keys(struct theatre *array_theatre, struct key_theatre *key_theatre_array, int array_theatre_length)
{
    int choice;

    choice = sort_menu();

    printf("Sorted array (by key array):\n");
    create_key_array(array_theatre, key_theatre_array, array_theatre_length, choice);

    switch (choice)
    {
//        case 1:
//            sort_key_array(key_theatre_array, array_theatre_length, compare_key_theatre_name);
//            break;
        case 2:
            sort_key_array(key_theatre_array, array_theatre_length, compare_key_play_name);
            break;
//        case 3:
//            sort_key_array(key_theatre_array, array_theatre_length, compare_key_price);
//            break;
    }

    print_key_sorted_array(array_theatre, key_theatre_array, array_theatre_length, choice);

    return choice;
}
