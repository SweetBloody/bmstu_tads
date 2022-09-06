#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "time_count.h"
#include "cdio.h"
#include "sorts.h"
#include "process.h"

#define N 1000

// Подсчет времени сортировки изначального массива (пузырь)
double initial_sort_time_bubble(struct theatre *array_theatre, int array_length)
{
    clock_t start, stop;
    double time = 0;
    struct theatre array_tmp[MAX_ARRAY_LEN];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < array_length; j++)
            array_tmp[j] = array_theatre[j];

        start = clock();
        sort_array(array_tmp, array_length, compare_play_name);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Подсчет времени сортировки изначального массива (qsort)
double initial_sort_time_qsort(struct theatre *array_theatre, int array_length)
{
    clock_t start, stop;
    double time = 0;
    struct theatre array_tmp[MAX_ARRAY_LEN];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < array_length; j++)
            array_tmp[j] = array_theatre[j];

        start = clock();
        qsort(array_tmp, array_length, sizeof(array_theatre[0]), compare_play_name);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Подсчет времени сортировки массива ключей (пузырь)
double key_sort_time_bubble(struct key_theatre *array_theatre, int array_length)
{
    clock_t start, stop;
    double time = 0;
    struct key_theatre array_tmp[MAX_ARRAY_LEN];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < array_length; j++)
            array_tmp[j] = array_theatre[j];

        start = clock();
        sort_key_array(array_tmp, array_length, compare_key_play_name);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Подсчет времени сортировки массива ключей (qsort)
double key_sort_time_qsort(struct key_theatre *array_theatre, int array_length)
{
    clock_t start, stop;
    double time = 0;
    struct key_theatre array_tmp[MAX_ARRAY_LEN];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < array_length; j++)
            array_tmp[j] = array_theatre[j];

        start = clock();
        qsort(array_tmp, array_length, sizeof(array_theatre[0]), compare_key_play_name);
        stop = clock();
        time += stop - start;
    }

    return time / N / CLOCKS_PER_SEC * 1000000;
}

// Поиск минимального времени
double min_time(double *time)
{
    double min = time[0];
    for (int i = 0; i < 4; i++)
        if (time[i] < min)
            min = time[i];

    return min;
}

// Поиск максимального времени
double max_time(double *time)
{
    double max = time[0];
    for (int i = 0; i < 4; i++)
        if (time[i] > max)
            max = time[i];

    return max;
}

// Анализ ввремени и памяти
void time_analysis(struct theatre *array_theatre, int array_length)
{
    int percent_1, percent_2;
    double time[4], min, max;
    struct key_theatre key_array_theatre_1[array_length], key_array_theatre_2[array_length];

    create_key_array(array_theatre, key_array_theatre_1, array_length, 2);
    create_key_array(array_theatre, key_array_theatre_2, array_length, 2);

    input_array_of_theatre("data.txt", array_theatre, &array_length);
    time[0] = initial_sort_time_bubble(array_theatre, array_length);

    input_array_of_theatre("data.txt", array_theatre, &array_length);
    time[1] = initial_sort_time_qsort(array_theatre, array_length);

    input_array_of_theatre("data.txt", array_theatre, &array_length);
    time[2] = key_sort_time_bubble(key_array_theatre_1, array_length);

    input_array_of_theatre("data.txt", array_theatre, &array_length);
    time[3] = key_sort_time_qsort(key_array_theatre_2, array_length);

    print_time_table(time[0], time[1], time[2], time[3]);

    percent_1 = abs((int)(time[0] / time[2] * 100) - 100);

    if (percent_1 == 0)
        percent_1 = 100;

    if ((int) time[0] - (int) time[2] == 0)
        percent_1 = 0;

    percent_2 = abs((int)(time[1] / time[3] * 100) % 100);

    if (time[3] == 0 || time[1] == 0)
        percent_2 = -1;

    if (percent_2 == 0)
        percent_2 = 100;

    if (time[3] == time[1])
        percent_2 = 0;

    if ((int) time[2] - (int) time[4] == 0)
        percent_1 = 0;

    min = min_time(time);
    max = max_time(time);

    print_time_analysis(percent_1, percent_2, (int) min, (int) max);
    print_memory_table(array_theatre, key_array_theatre_1, array_length);

    percent_1 = (int) (((double) sizeof(array_theatre[0]) * array_length) /
            ((double) sizeof(key_array_theatre_1[0]) * array_length) * 100) - 100;
    percent_2 = (int) ((double) sizeof(key_array_theatre_1[0]) /
            (double) sizeof(array_theatre[0]) * 100);

    print_memory_analysis(percent_1, percent_2);
}

