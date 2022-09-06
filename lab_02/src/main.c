#include <stdio.h>
#include "const.h"
#include "structs.h"
#include "file_process.h"
#include "cdio.h"
#include "sorts.h"
#include "process.h"
#include "delete.h"
#include "time_count.h"

int main(int argc, char **argv)
{
    struct theatre array_theatre[MAX_ARRAY_LEN];
    struct key_theatre key_theatre_array[MAX_ARRAY_LEN];
    int ch, key = -1, choice = -1, array_theatre_length;

    if (argc != 2)
    {
        ch = INCORRECT_ARGS;
        print_errors(ch);
        return ch;
    }

    ch = file_check(argv[1]);

    if (ch != OK)
    {
        print_errors(ch);
        return ch;
    }

    ch = input_array_of_theatre(argv[1], array_theatre, &array_theatre_length);

    if (ch != OK)
    {
        print_errors(ch);
        return ch;
    }

    create_key_array(array_theatre, key_theatre_array, array_theatre_length, 2);

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                ch = input_array_of_theatre(argv[1], array_theatre, &array_theatre_length);

                if (ch != OK)
                {
                    print_errors(ch);
                    return ch;
                }
                break;
            case 2:
                print_array_of_theatre(array_theatre, array_theatre_length);
                break;
            case 3:
                sort_initial_array_by_keys(array_theatre, array_theatre_length);
                print_array_of_theatre(array_theatre, array_theatre_length);
                break;
            case 4:
                key = sort_key_array_by_keys(array_theatre, key_theatre_array, array_theatre_length);
                break;
            case 5:
                print_key_array(key_theatre_array, array_theatre_length, key);

//                if (key != -1)
//                    print_key_array(key_theatre_array, array_theatre_length, key);
//                else
//                    printf("Use key sort first!\n");
                break;
            case 6:
                musical_find(array_theatre, array_theatre_length);
                break;
            case 7:
                input_theatre(stdin, &array_theatre[array_theatre_length]);
                array_theatre_length += 1;
                break;
            case 8:
                delete_menu(array_theatre, &array_theatre_length);
                break;
            case 9:
                time_analysis(array_theatre, array_theatre_length);
                break;
        }
    }

    return OK;
}
