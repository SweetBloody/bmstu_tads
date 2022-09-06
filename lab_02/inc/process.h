#ifndef LAB_02_PROCESS_H
#define LAB_02_PROCESS_H

#include "../inc/structs.h"

// Создание массива ключей
void create_key_array(struct theatre *array_theatre, struct key_theatre *key_array, int array_length, int key);

// Поиск и вывод необходимых спектаклей (по варианту)
void musical_find(struct theatre *array_theatre, int array_length);

#endif //LAB_02_PROCESS_H
