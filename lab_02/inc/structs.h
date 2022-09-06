#ifndef LAB_02_STRUCTS_H
#define LAB_02_STRUCTS_H

#include "const.h"

typedef struct
{
    int min_age;                                   // Возрастное ограничение
    int type_of_child_play;                        // Тип: 1 - сказка, 2 - пьеса
} child_play;

typedef struct
{
    int type_of_adult_play;                        // Тип: 1 - пьеса, 2 - драма, 3 - комедия
} adult_play;

typedef struct
{
    char composer_name[MAX_COMPOSER_NAME + 2];     // Композитор
    char country_name[MAX_COUNTRY_NAME + 2];       // Страна
    int min_age;                                   // Возрастное ограничение
    int play_duration;                             // Длительность мюзикла
} musical;

struct theatre
{
    char theatre_name[MAX_THEATRE_NAME + 2];       // Название театра
    char play_name[MAX_PLAY_NAME + 2];             // Название спектакля
    int start_price;                               // Начальная цена билета
    int end_price;                                 // Конечная цена билета
    int type_of_play;                              // Тип спектакля: 1 - детский, 2 - взрослый, 3 - мюзикл
    union
    {
        child_play child_play;                     // Детский спектакль
        adult_play adult_play;                     // Взрослый спектакль
        musical musical;                           // Мюзикл
    } type;
};

struct key_theatre{
//    char theatre_name[MAX_THEATRE_NAME + 2];       // Название театра
    char play_name[MAX_THEATRE_NAME + 2];          // Название спектакля
//    int delta;                                     // Диапазон цен
    int array_index;                               // Индекс в начальном массиве
};

#endif //LAB_02_STRUCTS_H
