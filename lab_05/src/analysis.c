#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include "analysis.h"
#include "process.h"
#include "list.h"
#include "array.h"

#define N 1

// Замер времени работы моделирования с помощью списка
int64_t time_analysis_list(double *time_set)
{
    model_t model;
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time = 0;

    for (int i = 0; i < N; i++)
    {
        init_model(&model);
        gettimeofday(&tv_start, NULL);
        modelling_list_queue(&model, time_set, 0);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL\
                        + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    return elapsed_time / N;
}

// Замер времени работы моделирования с помощью массива
int64_t time_analysis_array(double *time_set)
{
    model_t model;
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time = 0;

    for (int i = 0; i < N; i++)
    {
        init_model(&model);
        gettimeofday(&tv_start, NULL);
        modelling_array_queue(&model, time_set, 0);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL\
                        + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    return elapsed_time / N;
}

// Анализ сравнения моделирования с разными реализациями очередей
void analysis(double *time_set)
{
    int64_t time1, time2;

    printf("|-------------------------------|-------------------------------------|\n");
    printf("|            T1, T2             |         modelling time, ms          |\n");
    printf("|                               |------------------|------------------|\n");
    printf("|            T3, T4             |       list       |      array       |\n");
    printf("|-------------------------------|------------------|------------------|\n");

    time1 = time_analysis_list(time_set);
    time2 = time_analysis_array(time_set);
    printf("|%6.3lf -%6.3lf, %6.3lf -%6.3lf |                  |                  |\n",
           time_set[0], time_set[1], time_set[2], time_set[3]);
    printf("|                               |   %8d       |   %8d       |\n", (int) time1, (int) time2);
    printf("|%6.3lf -%6.3lf, %6.3lf -%6.3lf |                  |                  |\n",
           time_set[4], time_set[5], time_set[6], time_set[7]);
    printf("|-------------------------------|------------------|------------------|\n\n");

    printf("Memory:\n");
    printf("Struct pointer for list element (bytes): %ld\n", sizeof(list_queue_t));
    printf("Struct for array queue (bytes): %ld (for %d elements)\n", sizeof(array_queue_t), MAX_QUEUE_LEN);
    printf("Required memory for %d elements using list: %ld\n\n", MAX_QUEUE_LEN, sizeof(list_queue_t) * MAX_QUEUE_LEN);
}