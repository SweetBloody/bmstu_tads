#include <stdio.h>
#include <math.h>
#include "process.h"
#include "cdio.h"
#include "list.h"
#include "array.h"

#define EPS 0.0000001

// Обнуление данных об очереди
void init_queue(queue_t *queue)
{
    queue->cur_queue_len = 0;
    queue->avg_queue_len = 0;
    queue->in_amount = 0;
    queue->out_amount = 0;
    queue->avg_queue_time = 0;
}

// Обнуление данных о моделировании
void init_model(model_t *model)
{
    model->modeling_time = 0;
    model->stop_time = 0;
    model->in_amount_type_1 = 0;
    model->in_amount_type_2 = 0;
    model->out_amount_type_1 = 0;
    model->out_amount_type_2 = 0;
}

// Получение случайного значения времени
double get_time(double t1, double t2)
{
    double t;

    t = (double) rand() / RAND_MAX;

    return (t2 - t1) * t + t1;
}

// Минимальное из двух времен
double min(double time1, double time2)
{
    if (fabs(time1) < EPS)
        return time2;
    if (fabs(time2) < EPS)
        return time1;
    if (time1 < time2)
        return time1;
    else
        return time2;
}

// Моделирование процесса с помощью списка
void modelling_list_queue(model_t *model, double *time, char mode)
{
    list_queue_t *pin_1 = NULL, *pin_2 = NULL, *pout_1 = NULL, *pout_2 = NULL;
    queue_t queue_1, queue_2;
    int model_time_flag = 0;   // 0 - in, 1 - proc
    int sum_len_1 = 0, sum_len_2 = 0, index = 0;
    double time_in_1 = 0, time_in_2 = 0, time_machine = 0;
    double min_time;
    double avg_in_time_1 = (time[0] + time[1]) / 2;
    double avg_in_time_2 = (time[2] + time[3]) / 2;
    char machine = 0;
    FILE *file;

    // Запись адресов в файлa
    if (mode == 1)
        file = fopen("address.txt", "w");

    init_queue(&queue_1);
    init_queue(&queue_2);

    if (avg_in_time_1 < (time[4] + time[5]) / 2)
        model_time_flag = 1;

    while (model->out_amount_type_1 != 1000)
    {
        // Если закончилось время ожидания заявки (1 очередь)
        if (time_in_1 <= 0)
        {
            // Получение времени поступления заявки 1 типа
            time_in_1 = get_time(time[0], time[1]);

            // Увеличение общего времени моделирования
            if (model_time_flag == 0)
                model->modeling_time += time_in_1;

            // Поступление новой заявки 1 типа
            add_to_list_queue(&pin_1, 1);
            if (pout_1 == NULL)
                pout_1 = pin_1;
            queue_1.cur_queue_len += 1;
            queue_1.in_amount += 1;
            model->in_amount_type_1 += 1;

            // Запись адресов в файл
            if (mode == 1)
                fprintf(file, "Request_1 in: %16p\n", (void *) pin_1);
        }

        // Если закончилось время ожидания заявки (2 очередь)
        if (time_in_2 <= 0)
        {
            // Получение времени поступления заявки 2 типа
            time_in_2 = get_time(time[2], time[3]);

            // Поступление новой заявки 2 типа
            add_to_list_queue(&pin_2, 2);
            if (pout_2 == NULL)
                pout_2 = pin_2;
            queue_2.cur_queue_len += 1;
            queue_2.in_amount += 1;
            model->in_amount_type_2 += 1;

            // Запись адресов в файл
            if (mode == 1)
                fprintf(file, "Request_2 in: %16p\n", (void *) pin_2);
        }

        // Если закончилось время обработки заявки
        if (time_machine <= 0)
        {

            // Вывод результатов на каждую сотую обработанную заявку 1 типа
            if (machine == 1 && model->out_amount_type_1 % 100 == 0 && model->out_amount_type_1 != 0 && mode == 1)
            {
                // Расчет средней длины очередей
                queue_1.avg_queue_len = sum_len_1 / index;
                queue_2.avg_queue_len = sum_len_2 / index;

                // Расчет среднего времени пребывания заявок в очереди
                queue_1.avg_queue_time = queue_1.avg_queue_len * avg_in_time_1;
                queue_2.avg_queue_time = queue_2.avg_queue_len * avg_in_time_2;

                print_queue_info(queue_1, 1, model->out_amount_type_1);
                print_queue_info(queue_2, 2, model->out_amount_type_1);
            }

            // Поступление заявок из очередей в ОА
            if (queue_1.cur_queue_len > 0) // если в системе есть заявка 1 типа
            {
                // Запись адресов в файл
                if (mode == 1)
                    fprintf(file, "Request_1 out:%16p\n", (void *) pout_1);

                delete_from_list_queue(&pin_1, &pout_1);
                queue_1.cur_queue_len -= 1;
                queue_1.out_amount += 1;
                model->out_amount_type_1 += 1;
                machine = 1;

                // Получение времени обработки заявки 1 типа
                time_machine = get_time(time[4], time[5]);

                // Увеличение общего времени моделирования
                if (model_time_flag == 1)
                    model->modeling_time += time_machine;
            }
            else if (queue_2.cur_queue_len > 0) // если в системе есть заявка 2 типа
            {
                // Запись адресов в файл
                if (mode == 1)
                    fprintf(file, "Request_2 out:%16p\n", (void *) pout_2);

                delete_from_list_queue(&pin_2, &pout_2);
                queue_2.cur_queue_len -= 1;
                queue_2.out_amount += 1;
                model->out_amount_type_2 += 1;
                machine = 2;

                // Получение времени обработки заявки 2 типа
                time_machine = get_time(time[6], time[7]);

                // Увеличение общего времени моделирования
                if (model_time_flag == 1)
                    model->modeling_time += time_machine;
            }
            else // простой
                model->stop_time += min(time_in_1, time_in_2);
        }

        // Вычитание времени
        min_time = min(min(time_in_1, time_in_2), min(time_in_2, time_machine));

        time_in_1 -= min_time;
        time_in_2 -= min_time;
        time_machine -= min_time;

        // Увеличение суммы длин очередей для расчета средней
        sum_len_1 += queue_1.cur_queue_len;
        sum_len_2 += queue_2.cur_queue_len;
        index += 1;
    }

    free_list(&pin_1, &pout_1);
    free_list(&pin_2, &pout_2);

    // Запись адресов в файл
    if (mode == 1)
        fclose(file);
}

// Моделирование процесса с помощью массива
int modelling_array_queue(model_t *model, double *time, char mode)
{
    array_queue_t array_queue_1, array_queue_2;
    queue_t queue_1, queue_2;
    int model_time_flag = 0;   // 0 - in, 1 - proc
    int sum_len_1 = 0, sum_len_2 = 0, index = 0;
    double time_in_1 = 0, time_in_2 = 0, time_machine = 0;
    double min_time;
    double avg_in_time_1 = (time[0] + time[1]) / 2;
    double avg_in_time_2 = (time[2] + time[3]) / 2;
    char machine = 0;
    int ch;

    init_array_queue(&array_queue_1);
    init_array_queue(&array_queue_2);

    init_queue(&queue_1);
    init_queue(&queue_2);

    if (avg_in_time_1 < (time[4] + time[5]) / 2)
        model_time_flag = 1;

    while (model->out_amount_type_1 != 1000)
    {
        // Если закончилось время ожидания заявки (1 очередь)
        if (time_in_1 <= 0)
        {
            // Получение времени поступления заявки 1 типа
            time_in_1 = get_time(time[0], time[1]);

            // Увеличение общего времени моделирования
            if (model_time_flag == 0)
                model->modeling_time += time_in_1;

            // Поступление новой заявки 1 типа
            ch = add_to_array_queue(&array_queue_1, 1);
            if (ch != OK)
                return ch + 1;
            queue_1.cur_queue_len += 1;
            queue_1.in_amount += 1;
            model->in_amount_type_1 += 1;
        }

        // Если закончилось время ожидания заявки (2 очередь)
        if (time_in_2 <= 0)
        {
            // Получение времени поступления заявки 2 типа
            time_in_2 = get_time(time[2], time[3]);

            // Поступление новой заявки 2 типа
            ch = add_to_array_queue(&array_queue_2, 1);
            if (ch != OK)
                return ch + 2;
            queue_2.cur_queue_len += 1;
            queue_2.in_amount += 1;
            model->in_amount_type_2 += 1;
        }

        // Если закончилось время обработки заявки
        if (time_machine <= 0)
        {

            // Вывод результатов на каждую сотую обработанную заявку 1 типа
            if (machine == 1 && model->out_amount_type_1 % 100 == 0 && model->out_amount_type_1 != 0 && mode == 1)
            {
                // Расчет средней длины очередей
                queue_1.avg_queue_len = sum_len_1 / index;
                queue_2.avg_queue_len = sum_len_2 / index;

                // Расчет среднего времени пребывания заявок в очереди
                queue_1.avg_queue_time = queue_1.avg_queue_len * avg_in_time_1;
                queue_2.avg_queue_time = queue_2.avg_queue_len * avg_in_time_2;

                print_queue_info(queue_1, 1, model->out_amount_type_1);
                print_queue_info(queue_2, 2, model->out_amount_type_1);
            }

            // Поступление заявок из очередей в ОА
            if (queue_1.cur_queue_len > 0) // если в системе есть заявка 1 типа
            {
                delete_from_array_queue(&array_queue_1);
                queue_1.cur_queue_len -= 1;
                queue_1.out_amount += 1;
                model->out_amount_type_1 += 1;
                machine = 1;

                // Получение времени обработки заявки 1 типа
                time_machine = get_time(time[4], time[5]);

                // Увеличение общего времени моделирования
                if (model_time_flag == 1)
                    model->modeling_time += time_machine;
            }
            else if (queue_2.cur_queue_len > 0) // если в системе есть заявка 2 типа
            {
                delete_from_array_queue(&array_queue_2);
                queue_2.cur_queue_len -= 1;
                queue_2.out_amount += 1;
                model->out_amount_type_2 += 1;
                machine = 2;

                // Получение времени обработки заявки 2 типа
                time_machine = get_time(time[6], time[7]);

                // Увеличение общего времени моделирования
                if (model_time_flag == 1)
                    model->modeling_time += time_machine;
            }
            else // простой
                model->stop_time += min(time_in_1, time_in_2);
        }

        // Вычитание времени
        min_time = min(min(time_in_1, time_in_2), min(time_in_2, time_machine));

        time_in_1 -= min_time;
        time_in_2 -= min_time;
        time_machine -= min_time;

        // Увеличение суммы длин очередей для расчета средней
        sum_len_1 += queue_1.cur_queue_len;
        sum_len_2 += queue_2.cur_queue_len;
        index += 1;
    }

    return OK;
}