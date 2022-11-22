#include <stdio.h>
#include <math.h>
#include "cdio.h"

// Настройка времен для моделирования
void time_settings(double *time)
{
    int ch = 0;

    while (ch != 2 || time[0] < 0 || time[1] < 0)
    {
        setbuf(stdin, NULL);
        printf("'In time' for 1 type:\n");
        ch = scanf("%lf%lf", &time[0], &time[1]);
    }

    ch = 0;
    while (ch != 2 || time[2] < 0 || time[3] < 0)
    {
        setbuf(stdin, NULL);
        printf("'In time' for 2 type:\n");
        ch = scanf("%lf%lf", &time[2], &time[3]);
    }

    ch = 0;
    while (ch != 2 || time[4] < 0 || time[5] < 0)
    {
        setbuf(stdin, NULL);
        printf("'Process time' for 1 type:\n");
        ch = scanf("%lf%lf", &time[4], &time[5]);
    }

    ch = 0;
    while (ch != 2 || time[6] < 0 || time[7] < 0)
    {
        setbuf(stdin, NULL);
        printf("'Process time' for 2 type:\n");
        ch = scanf("%lf%lf", &time[6], &time[7]);
    }
}

// Вывод информации о состоянии очереди
void print_queue_info(queue_t queue, char type, int amount)
{
    if (type == 1)
        printf("\n--------------- %4d ---------------\n", amount);

    printf("Queue %d:\n", type);
    printf("  Current queue length: %d\n", queue.cur_queue_len);
    printf("  Average queue length: %d\n", queue.avg_queue_len);
    printf("  Amount of in requests: %d\n", queue.in_amount);
    printf("  Amount of out requests: %d\n", queue.out_amount);
    printf("  Average time in queue: %lf\n", queue.avg_queue_time);
}

// Вывод результатов моделирования
void print_modelling_info(model_t model)
{
    printf("\n--------- Modelling results ---------\n");
    printf("Amount of in requests  (1 type): %d\n", model.in_amount_type_1);
    printf("Amount of out requests (1 type): %d\n", model.out_amount_type_1);
    printf("Amount of in requests  (2 type): %d\n", model.in_amount_type_2);
    printf("Amount of out requests (2 type): %d\n", model.out_amount_type_2);
    printf("Total modelling time: %lf\n", model.modeling_time);
    printf("Total stop time: %lf\n", model.stop_time);
}

// Анализ моделирования
void print_analysis(model_t model, double *time)
{
    double theor_time, percent;

    if ((time[0] + time[1]) / 2 < (time[4] + time[5]) / 2)
        theor_time = (time[4] + time[5]) / 2 * 1000;
    else
        theor_time = (time[0] + time[1]) / 2 * 1000;

    percent = fabs(model.modeling_time - theor_time) / theor_time * 100;

    printf("Expected theoretical modelling time: %lf\n", theor_time);
    printf("Defect: %lf\n\n", percent);
}

// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|-------------------------------------------------|\n");
    printf("| MENU:                                           |\n");
    printf("|  1 - modeling with array;                       |\n");
    printf("|  2 - modeling with list;                        |\n");
    printf("|  3 - time settings;                             |\n");
    printf("|  4 - analysis;                                  |\n");
    printf("|  0 - exit;                                      |\n");
    printf("|-------------------------------------------------|\n");
    printf("Your choice (from 0 to 4):\n");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    while (ch != 1 || number < 0 || number > 4)
    {
        printf("Please enter numbers from 0 to 4:\n");
        ch = scanf("%d", &number);
        scanf("%c", &n);
    }

    return number;
}