#ifndef LAB_05_PROCESS_H
#define LAB_05_PROCESS_H

#include <stdlib.h>
#include <time.h>

// Структура данных об очереди
typedef struct
{
    int cur_queue_len;      // Текущая длина очереди
    int avg_queue_len;      // Средняя длина очереди
    int in_amount;          // Количество вошедших заявок
    int out_amount;         // Количество вышедших заявок
    double avg_queue_time;  // Среднее время пребывания заявок в очереди
} queue_t;

// Структура данных моделирования
typedef struct
{
    double modeling_time;   // Общее время моделирования
    double stop_time;       // Время простоя
    int in_amount_type_1;   // Количество вошедших в систему заявок 1 типа
    int in_amount_type_2;   // Количество вошедших в систему заявок 2 типа
    int out_amount_type_1;  // Количество вышедших из системы заявок 1 типа
    int out_amount_type_2;  // Количество вышедших из системы заявок 2 типа
} model_t;

// Обнуление данных об очереди
void init_queue(queue_t *queue);

// Обнуление данных о моделировании
void init_model(model_t *model);

// Получение случайного значения времени
double get_time(double t1, double t2);

// Моделирование процесса с помощью списка
void modelling_list_queue(model_t *model, double *time, char mode);

// Моделирование процесса с помощью массива
int modelling_array_queue(model_t *model, double *time, char mode);

#endif //LAB_05_PROCESS_H
