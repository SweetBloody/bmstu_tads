#ifndef LAB_05_CDIO_H
#define LAB_05_CDIO_H

#include "process.h"

// Настройка времен для моделирования
void time_settings(double *time);

// Вывод информации о состоянии очереди
void print_queue_info(queue_t queue, char type, int amount);

// Вывод результатов моделирования
void print_modelling_info(model_t model);

// Анализ моделирования
void print_analysis(model_t model, double *time);

// Вывод меню
int print_menu();

#endif //LAB_05_CDIO_H
