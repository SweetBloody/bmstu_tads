#include <string.h>
#include "delete.h"
#include "cdio.h"

// Удалить структуру из массива
void delete_theatre_by_key(struct theatre *array_theatre, int *array_length, int index)
{
    for (int i = index; i < *array_length; i++)
        array_theatre[i] = array_theatre[i + 1];

    *array_length -= 1;
}

// Меню удаления
void delete_menu(struct theatre *array_theatre, int *array_length)
{
    int number, key;
    char string[MAX_PLAY_NAME + 2];

    key = input_delete_parameters(&number, string);

    for (int i = 0; i < *array_length; i++)
    {
        switch (key)
        {
            case 1:
                if (strcmp(array_theatre[i].theatre_name, string) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 2:
                if (strcmp(array_theatre[i].play_name, string) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 3:
                if ((array_theatre[i].end_price - array_theatre[i].start_price) == number)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 4:
                if (array_theatre[i].type_of_play == number)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
        }
    }
}