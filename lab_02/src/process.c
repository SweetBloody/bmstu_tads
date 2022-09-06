#include <stdio.h>
#include <string.h>
#include "process.h"
#include "cdio.h"

// Создание массива ключей
void create_key_array(struct theatre *array_theatre, struct key_theatre *key_array, int array_length, int key)
{
    switch (key)
    {
//        case 1:
//            for (int i = 0; i < array_length; i++)
//            {
//                key_array[i].array_index = i;
//                strcpy(key_array[i].theatre_name, array_theatre[i].theatre_name);
//            }
//            break;
        case 2:
            for (int i = 0; i < array_length; i++)
            {
                key_array[i].array_index = i;
                strcpy(key_array[i].play_name, array_theatre[i].play_name);
            }
            break;
//        case 3:
//            for (int i = 0; i < array_length; i++)
//            {
//                key_array[i].array_index = i;
//                key_array[i].delta = array_theatre[i].end_price - array_theatre[i].start_price;
//            }
//            break;
    }
}

// Поиск и вывод необходимых спектаклей (по варианту)
void musical_find(struct theatre *array_theatre, int array_length)
{
    int age, max_duration, index = 0;

    input_find_parameters(&age, &max_duration);

    printf("Musicals for %d year old "
           "children with duration less than %d hours:\n", age, max_duration);

    for (int i = 0; i < array_length; i++)
        if (array_theatre[i].type_of_play == 3 &&
        array_theatre[i].type.musical.min_age < age &&
        array_theatre[i].type.musical.play_duration < max_duration)
        {
            print_theatre_info(array_theatre[i], index);
            index += 1;
        }

    if (index == 0)
        printf("There are no such musicals.\n");
}