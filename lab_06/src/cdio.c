#include <stdio.h>
#include <string.h>
#include "cdio.h"
#include "const.h"

// Проверка файла
int file_check(char *filename, char *mode)
{
    FILE *f = fopen(filename, mode);
    char n;

    if (f == NULL)
        return FILE_OPEN_ERR;

    if (ferror(f) != 0)
        return FILE_ERR;

    if (fscanf(f, "%c", &n) != 1)
        return EMPTY_FILE;

    if (fclose(f) == EOF)
        return FILE_CLOSE_ERR;

    return OK;
}

// Чтение строки из файла
int read_string(FILE *f, char *string)
{
    char *ch;

    ch = fgets(string, LEN + 2, f);

    if (ch == NULL)
        return INCORRECT_INPUT;

    if (string[0] == '\0' || string[0] == '\n' || string[0] == '\t')
        return EMPTY_STR;

    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';

    return OK;
}

// Ввод слова для добавления
void input_word(char *word)
{
    int ch = 0;

    while (ch != 1)
    {
        setbuf(stdout, NULL);
        setbuf(stdin, NULL);
        printf("Input a word to add to trees and HASH table:\n");
        ch = scanf("%s", word);
    }
}

// Ввод размерности HASH таблицы
void input_hash_size(int *size)
{
    int ch = 0;

    while (ch != 1 || *size <= 0)
    {
        setbuf(stdout, NULL);
        setbuf(stdin, NULL);
        printf("Input size of HASH table:\n");
        ch = scanf("%d", size);
    }
}

// Подсчет количества слов в файле
int count_words(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    char word[LEN];
    int sum = 0;

    while(!feof(file))
    {
        read_string(file, word);
        sum++;
    }

    fclose(file);
    return sum;
}

// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|-------------------------------------------------|\n");
    printf("| MENU:                                           |\n");
    printf("|  1 - input data from file to bin/AVL tree;      |\n");
    printf("|  2 - print bin tree;                            |\n");
    printf("|  3 - print AVL tree;                            |\n");
    printf("|  4 - input data from file to HASH table;        |\n");
    printf("|  5 - print HASH table;                          |\n");
    printf("|  6 - restruct HASH table;                       |\n");
    printf("|  7 - add a word;                                |\n");
    printf("|  8 - analysis;                                  |\n");
    printf("|  0 - exit;                                      |\n");
    printf("|-------------------------------------------------|\n");
    printf("Your choice (from 0 to 8):\n");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    while (ch != 1 || number < 0 || number > 8)
    {
        printf("Please enter numbers from 0 to 8:\n");
        ch = scanf("%d", &number);
        scanf("%c", &n);
    }

    return number;
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

    if (ch == EMPTY_STR)
        printf("EMPTY_FILE\n");

    if (ch == INCORRECT_INPUT)
        printf("INCORRECT_INPUT\n");

    if (ch == MEMORY_ERR)
        printf("MEMORY_ERR\n");

    if (ch == EMPTY_FILE)
        printf("EMPTY_FILE\n");

}
