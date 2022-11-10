#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "cdio.h"

// Ввод значения элемента
void input_number(int *number)
{
    int ch = 0;

    while (ch != 1)
    {
        setbuf(stdin, NULL);
        printf("Input the value of new element to add:\n");
        ch = scanf("%d", number);
    }
}

// Инициализация стека списком
struct list_stack_t *init_list_stack(int number)
{
    struct list_stack_t *list_stack;

    list_stack = (struct list_stack_t *) malloc(sizeof(struct list_stack_t));

    if (list_stack)
    {
        list_stack->number = number;
        list_stack->prev = NULL;
    }

    return list_stack;
}

// Вывод значений элементов стека (список)
void print_list_stack(struct list_stack_t *pointer, int len)
{
    struct list_stack_t *cur = pointer;
    int *array = malloc(len * sizeof(int)), index = 0;

    printf("Stack (list):\n");

    while (cur->prev != NULL)
    {
        array[index] = cur->number;
        cur = cur->prev;
        index += 1;
    }
    array[index] = cur->number;

    for (int i = index; i >= 0; i--)
        printf("%4d", array[i]);
    printf("\n");

    free(array);
}

// Вывод адресов элементов стека (список)
void print_list_stack_address(struct list_stack_t *pointer, struct mem_array_t mem_array, int len)
{
    struct list_stack_t *cur = pointer;
    int *array = malloc(len * sizeof(int)), index = 0;
    struct list_stack_t **mem = malloc(len * sizeof(struct list_stack_t*));

    while (cur->prev != NULL)
    {
        array[index] = cur->number;
        mem[index] = cur;
        cur = cur->prev;
        index += 1;
    }
    array[index] = cur->number;
    mem[index] = cur;

    printf("Stack (list):\n");

    printf("|--------------------|----------------------|\n");
    printf("|        elem        |        memory        |\n");
    printf("|--------------------|----------------------|\n");

    for (int i = index; i >= 0; i--)
    {
        printf("|%17d   |%19p   |\n", array[i], (void*) mem[i]);
        printf("|--------------------|----------------------|\n");
    }

    if (mem_array.index != 0)
        printf("Addresses that got free:\n");

    for (int i = 0; i < mem_array.index; i++)
        printf("%p\n", (void*) mem_array.data[i]);

    free(array);
    free(mem);
}

// Инициализация стека массивом
void init_array_stack(array_stack_t *array_stack)
{
    array_stack->pointer = array_stack->data - 1;
    array_stack->start = array_stack->data;
    array_stack->end = array_stack->start + MAX_STACK_LEN;
}

// Вывод стека (массив)
void print_array_stack(array_stack_t array_stack)
{
    int *pa = array_stack.start;

    printf("Stack (array):\n");

    while (pa <= array_stack.pointer)
    {
        printf("%4d", *pa);
        pa += 1;
    }

    printf("\n");
}

// Вывод меню
int print_menu()
{
    int number, ch;
    char n;

    printf("|-------------------------------------------------|\n");
    printf("| MENU:                                           |\n");
    printf("|  1 - add element to stack (array);              |\n");
    printf("|  2 - add element to stack (list);               |\n");
    printf("|  3 - delete element from stack (array);         |\n");
    printf("|  4 - delete element from stack (list);          |\n");
    printf("|  5 - print stack (array);                       |\n");
    printf("|  6 - print stack (list);                        |\n");
    printf("|  7 - print stack with address (list);           |\n");
    printf("|  8 - print decreasing sets in reverse (array);  |\n");
    printf("|  9 - print decreasing sets in reverse (list);   |\n");
    printf("| 10 - time and memory analysis;                  |\n");
    printf("| 11 - adding and deleting time analysis;         |\n");
    printf("|  0 - exit;                                      |\n");
    printf("|-------------------------------------------------|\n");
    printf("Your choice (from 0 to 11):\n");

    ch = scanf("%d", &number);
    scanf("%c", &n);

    while (ch != 1 || number < 0 || number > 11)
    {
        printf("Please enter numbers from 0 to 11:\n");
        ch = scanf("%d", &number);
        scanf("%c", &n);
    }

    return number;
}