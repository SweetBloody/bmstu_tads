#include <stdio.h>
#include <string.h>
#include "const.h"
#include "cdio.h"

// Ввод строки
int input_string(FILE *file, char *string, int max_len, int error)
{
    char *ch;

    ch = fgets(string, max_len + 2, file);

    if (ch == NULL)
        return INCORRECT_INPUT;

    if (strlen(string) > max_len)
        return error;

    if (string[0] == '\n')
        return EMPTY_STRING;

    string[strlen(string) - 1] = '\0';

    return OK;
}

int input_int_number(FILE *file, int *number)
{
    int ch = fscanf(file, "%d", number);
    char n;

    if (ch != 1 || *number < 0)
        return INCORRECT_INPUT;


    fscanf(file, "%c", &n);

    return OK;
}

// Ввод подструктуры child_play
int input_child_play(FILE *file, struct theatre *theatre)
{
    int ch, min_age, type_of_child_play;

    if (file == stdin)
        printf("Enter the minimum age:\n");

    ch = input_int_number(file, &min_age);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("1 - fairy tale\n"
               "2 - play\n"
               "Enter the type of the play:\n");

    ch = input_int_number(file, &type_of_child_play);

    if (ch != OK)
        return ch;

    theatre->type.child_play.min_age = min_age;
    theatre->type.child_play.type_of_child_play = type_of_child_play;

    return OK;
}

// Ввод подструктуры adult_play
int input_adult_play(FILE *file, struct theatre *theatre)
{
    int ch, type_of_adult_play;

    if (file == stdin)
        printf("1 - play\n"
               "2 - drama\n"
               "3 - comedy\n"
               "Enter the type of the play:\n");

    ch = input_int_number(file, &type_of_adult_play);

    if (ch != OK)
        return ch;

    theatre->type.adult_play.type_of_adult_play = type_of_adult_play;

    return OK;
}

// Ввод подструктуры musical
int input_musical(FILE *file, struct theatre *theatre)
{
    char composer_name[MAX_COMPOSER_NAME + 2], country_name[MAX_COUNTRY_NAME + 2];
    int ch, min_age, play_duration;

    if (file == stdin)
        printf("Enter the composer name:\n");

    ch = input_string(file, composer_name, MAX_COMPOSER_NAME, COMPOSER_NAME_OVERFLOW);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter the country name:\n");

    ch = input_string(file, country_name, MAX_COUNTRY_NAME, COUNTRY_NAME_OVERFLOW);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter the minimum age:\n");

    ch = input_int_number(file, &min_age);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter play duration:\n");

    ch = input_int_number(file, &play_duration);

    if (ch != OK)
        return ch;

    strcpy(theatre->type.musical.composer_name, composer_name);
    strcpy(theatre->type.musical.country_name, country_name);
    theatre->type.musical.min_age = min_age;
    theatre->type.musical.play_duration = play_duration;

    return OK;
}

// Ввод структуры theatre
int input_theatre(FILE *file, struct theatre *theatre)
{
    char theatre_name[MAX_THEATRE_NAME + 2], play_name[MAX_PLAY_NAME + 2];
    int start_price, end_price, type_of_play, ch;

    if (file == stdin)
        printf("Enter the name of theatre:\n");

    ch = input_string(file, theatre_name, MAX_THEATRE_NAME, THEATRE_NAME_OVERFLOW);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter the name of play:\n");

    ch = input_string(file, play_name, MAX_PLAY_NAME, PLAY_NAME_OVERFLOW);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter the start price:\n");

    ch = input_int_number(file, &start_price);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("Enter the end price:\n");

    ch = input_int_number(file, &end_price);

    if (ch != OK)
        return ch;

    if (file == stdin)
        printf("1 - child play\n"
               "2 - adult_play\n"
               "3 - musical\n"
               "Enter the type of the play:\n");

    ch = input_int_number(file, &type_of_play);

    if (ch != OK)
        return ch;

    strcpy(theatre->theatre_name, theatre_name);
    strcpy(theatre->play_name, play_name);
    theatre->start_price = start_price;
    theatre->end_price = end_price;
    theatre->type_of_play = type_of_play;

    if (type_of_play == 1)
        ch = input_child_play(file, theatre);
    else if (type_of_play == 2)
        ch = input_adult_play(file, theatre);
    else if (type_of_play == 3)
        ch = input_musical(file, theatre);
    else
        return INCORRECT_VALUE;

    if (ch != OK)
        return ch;

    return OK;
}

// Ввод массива структур theatre
int input_array_of_theatre(char *file_name, struct theatre *array_theatre, int *array_theatre_length)
{
    int ch;
    FILE *file = fopen(file_name, "r");

    *array_theatre_length = 0;

    while (!feof(file))
    {
        ch = input_theatre(file, &array_theatre[*array_theatre_length]);

        if (ch != OK)
        {
            fclose(file);
            return ch;
        }

        *array_theatre_length += 1;

        if (*array_theatre_length == MAX_ARRAY_LEN)
            return THEATRE_ARRAY_OVERFLOW;
    }

    if (*array_theatre_length == 0)
    {
        fclose(file);
        return EMPTY_FILE;
    }

    fclose(file);

    return OK;
}

// Вывод данных о структуре theatre
void print_theatre_info(struct theatre theatre, int num)
{
    printf("------------------#%d------------------\n", num + 1);
    printf("Theatre name:   %s\n", theatre.theatre_name);
    printf("Play name:      %s\n", theatre.play_name);
    printf("Price range:    %d - ", theatre.start_price);
    printf("%d\n", theatre.end_price);

    if (theatre.type_of_play == 1)
    {
        printf("Type of play:   Child play\n");
        printf("Minimum age:    %d\n", theatre.type.child_play.min_age);

        if (theatre.type.child_play.type_of_child_play == 1)
            printf("Type:           Fairy tale\n");
        else
            printf("Type:           Play\n");
    }
    else if (theatre.type_of_play == 2)
    {
        printf("Type of play:   Adult play\n");

        if (theatre.type.adult_play.type_of_adult_play == 1)
            printf("Type:           Play\n");
        else if (theatre.type.adult_play.type_of_adult_play == 2)
            printf("Type:           Drama\n");
        else
            printf("Type:           Comedy\n");
    }
    else
    {
        printf("Type of play:   Musical\n");
        printf("Composer name:  %s\n", theatre.type.musical.composer_name);
        printf("Country name:   %s\n", theatre.type.musical.country_name);
        printf("Minimum age:    %d\n", theatre.type.musical.min_age);
        printf("Play duration:  %d\n", theatre.type.musical.play_duration);
    }
    printf("---------------------------------------\n\n");
}

// Вывод массива структур theatre
void print_array_of_theatre(struct theatre *array_theatre, int array_theatre_length)
{
    for (int i = 0; i < array_theatre_length; i++)
        print_theatre_info(array_theatre[i], i);
}

// Вывод данных о структуре key_theatre
void print_key_theatre_info(struct key_theatre theatre, int key, int num)
{
    printf("------------------#%d------------------\n", num + 1);
    printf("Index:          %d\n", theatre.array_index);

    switch (key)
    {
//        case 1:
//            printf("Theatre name:   %s\n", theatre.theatre_name);
//            break;
        case 2:
            printf("Play name:      %s\n", theatre.play_name);
            break;
//        case 3:
//            printf("Delta:          %d\n", theatre.delta);
//            break;
    }

    printf("---------------------------------------\n\n");
}

// Вывод массива структур key_theatre (ключей)
void print_key_array(struct key_theatre *array_theatre, int array_theatre_length, int key)
{
    for (int i = 0; i < array_theatre_length; i++)
        print_key_theatre_info(array_theatre[i], key, i);
}

// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|------------------------------------------|\n");
    printf("| MENU:                                    |\n");
    printf("|  1 - reload array from the file;         |\n");
    printf("|  2 - print array of the structures;      |\n");
    printf("|  3 - sort initial array by keys;         |\n");
    printf("|  4 - sort with key array by keys;        |\n");
    printf("|  5 - print sorted key array;             |\n");
    printf("|  6 - find musical for children;          |\n");
    printf("|  7 - add one more structure;             |\n");
    printf("|  8 - delete structures by the key value; |\n");
    printf("|  9 - time and memory analysis;           |\n");
    printf("|  0 - exit;                               |\n");
    printf("|------------------------------------------|\n");
    printf("Your choice (from 0 to 9):\n");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    if (ch != 1 || number < 0 || number > 9)
    {
        printf("Please enter numbers from 0 to 9!\n");
        return RELOAD_MENU;
    }

    return number;
}

// Меню для сортировки исходной таблицы
int sort_menu()
{
    int choice, ch;

    printf("Choose the key for the sort:\n 1 - theatre name;\n 2 - play name;\n 3 - price;\n");

    ch = scanf("%d", &choice);

    while (ch != 1 || choice < 1 || choice > 3)
    {
        printf("Please enter numbers from 1 to 3!\n");
        ch = scanf("%d", &choice);
    }

    return choice;
}

// Вывод массива в отсортированном виде с помощью массива ключей
void print_key_sorted_array(struct theatre *array_theatre, struct key_theatre *key_theatre, int array_theatre_length, int key)
{
    switch (key)
    {
        case 1:
            for (int i = 0; i < array_theatre_length; i++)
                print_theatre_info(array_theatre[key_theatre[i].array_index], i);
            break;
        case 2:
            for (int i = 0; i < array_theatre_length; i++)
                print_theatre_info(array_theatre[key_theatre[i].array_index], i);
            break;
        case 3:
            for (int i = 0; i < array_theatre_length; i++)
                print_theatre_info(array_theatre[key_theatre[i].array_index], i);
            break;
    }
}

// Ввод параметров поиска мюзикла
void input_find_parameters(int *age, int *max_duration)
{
    int ch;

    printf("Enter tha age of a child:\n");
    ch = scanf("%d", age);

    while (ch != 1 || *age <= 0)
    {
        printf("Enter tha age of a child:\n");
        ch = scanf("%d", age);
    }

    printf("Enter tha maximum duration of the musical:\n");
    ch = scanf("%d", max_duration);

    while (ch != 1 || *max_duration <= 0)
    {
        printf("Enter tha maximum duration of the musical:\n");
        ch = scanf("%d", max_duration);
    }
}

// Ввод параметров удаления
int input_delete_parameters(int *number, char *string)
{
    int ch, key;
    char n;

    printf("Keys to delete:\n"
           "1 - theatre name\n"
           "2 - play name\n"
           "3 - price range\n"
           "4 - type of play\n"
           "Enter the key:\n");

    ch = scanf("%d", &key);
    scanf("%c", &n);

    while (ch != 1 || key < 1 || key > 4)
    {
        printf("Enter the key (1 - 4):\n");
        ch = scanf("%d", &key);
        scanf("%c", &n);
    }
    ch = 0;

    if (key == 1)
    {
        printf("Enter the theatre name:\n");
        fgets(string, MAX_PLAY_NAME + 2, stdin);
        string[strlen(string) - 1] = '\0';
    }
    else if (key == 2)
    {
        printf("Enter the play name:\n");
        fgets(string, MAX_PLAY_NAME + 2, stdin);
        string[strlen(string) - 1] = '\0';
    }
    else if (key == 3)
    {
        while (ch != 1 || *number < 0)
        {
            printf("Enter the price range:\n");
            ch = scanf("%d", number);
        }
    }
    else
    {
        while (ch != 1 || *number < 0)
        {
            printf("1 - child play\n"
                   "2 - adult_play\n"
                   "3 - musical\n"
                   "Enter the type of the play:\n");
            ch = scanf("%d", number);
        }
    }

    return key;
}

// Вывод таблицы значений времени
void print_time_table(double time_1, double time_2, double time_3, double time_4)
{
    printf(" Time, ms\n");
    printf("|----------|-----------------|-----------------|\n");
    printf("|          |  Initial array  |    Key array    |\n");
    printf("|----------|-----------------|-----------------|\n");
    printf("|  bubble  |  %13.1f  |  %13.1f  |\n", time_1, time_3);
    printf("|----------|-----------------|-----------------|\n");
    printf("|  qsort   |  %13.1f  |  %13.1f  |\n", time_2, time_4);
    printf("|----------|-----------------|-----------------|\n");
}

// Вывод различий во времени
void print_time_analysis(int percent_1, int percent_2, int min, int max)
{
    printf("Bubble sort:\n"
           "Sorting initial array is %d percent slower than sorting key array.\n", percent_1);

    if (percent_2 == -1)
        printf("Qsort:\n"
               "Impossible to count (the sorting is too fast).\n");
    else
        printf("Qsort:\n"
            "Sorting initial array is %d percent slower than sorting key array.\n", percent_2);

    printf("Minimum vs maximum:\n");
    if (min == 0)
        printf("Impossible to count (the sorting is too fast).\n\n");
    else
        printf("The fastest method of sorting is %d "
               "times faster than the slowest one.\n\n", max / min);
}

// Вывод таблицы значений памяти
void print_memory_table(struct theatre *array_theatre, struct key_theatre *array_key_theatre, int length)
{
    printf(" Memory\n");
    printf("|----------|-----------------|-----------------|\n");
    printf("|          |  Initial array  |    Key array    |\n");
    printf("|----------|-----------------|-----------------|\n");
    printf("|   array  |  %13llu  |  %13llu  |\n",
           sizeof(array_theatre[0]) * length, sizeof(array_key_theatre[0]) * length);
    printf("|----------|-----------------|-----------------|\n");
    printf("|  element |  %13llu  |  %13llu  |\n",
           sizeof(array_theatre[0]), sizeof(array_key_theatre[0]));
    printf("|----------|-----------------|-----------------|\n");
}

// Вывод различий в памяти
void print_memory_analysis(int percent_1, int percent_2)
{
    printf("Initial array is %d percent larger than key array.\n", percent_1);
    printf("We should use %d more percents of memory to use key array.\n\n", percent_2);
}

// Вывод сообщений об ошибках
void print_errors(int ch)
{
    if (ch == INCORRECT_ARGS)
        printf("INCORRECT_ARGS\n");

    if (ch == FILE_OPEN_ERR)
        printf("FILE_OPEN_ERR\n");

    if (ch == FILE_CLOSE_ERR)
        printf("FILE_CLOSE_ERR\n");

    if (ch == FILE_ERR)
        printf("FILE_ERR\n");

    if (ch == EMPTY_FILE)
        printf("EMPTY_FILE\n");

    if (ch == INCORRECT_INPUT)
        printf("INCORRECT_INPUT\n");

    if (ch == INCORRECT_VALUE)
        printf("INCORRECT_VALUE\n");

    if (ch == EMPTY_STRING)
        printf("EMPTY_STRING\n");

    if (ch == THEATRE_NAME_OVERFLOW)
        printf("THEATRE_NAME_OVERFLOW\n");

    if (ch == PLAY_NAME_OVERFLOW)
        printf("PLAY_NAME_OVERFLOW\n");

    if (ch == COMPOSER_NAME_OVERFLOW)
        printf("COMPOSER_NAME_OVERFLOW\n");

    if (ch == COUNTRY_NAME_OVERFLOW)
        printf("COUNTRY_NAME_OVERFLOW\n");

    if (ch == THEATRE_ARRAY_OVERFLOW)
        printf("THEATRE_ARRAY_OVERFLOW\n");
}
