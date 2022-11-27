#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "const.h"
#include "cdio.h"

// HASH функция
static int hash_function(char *word, int size)
{
    int index, sum = 0;
    char *p = word;

    while (*p != '\0')
    {
        sum += *p;
        p++;
    }

    index = sum % size;

    return index;
}

// Проход по списку до конца
static table_node_t *to_tail(table_node_t *head, char *word, int *cmp_num)
{
    table_node_t *cur = head;

    while (cur->next != NULL)
    {
        *cmp_num += 1;
        if (strcmp(cur->word, word) == 0)
            return NULL;

        cur = cur->next;
    }

    *cmp_num += 1;
    if (strcmp(cur->word, word) == 0)
        return NULL;

    return cur;
}

// Инициализация массива указателей нулями
static void init_hash_table(hash_table_t *hash_table)
{
    for (int i = 0; i < hash_table->size; i++)
        hash_table->table[i] = NULL;
}

// Добавление добавление элемента в HASH таблицу
int add_to_hash_table(char *word, hash_table_t *hash_table, int *cmp_num)
{
    int index;
    table_node_t *cur = NULL;
    table_node_t *node;

    if (hash_table->table == NULL)
    {
        hash_table->size = 1;
        hash_table->table = malloc(sizeof(table_node_t));
        init_hash_table(hash_table);
    }

    index = hash_function(word, hash_table->size);

    if (hash_table->table[index] != NULL)
        cur = to_tail(hash_table->table[index], word, cmp_num);

    if (cur == NULL && hash_table->table[index] != NULL)
        return OK;

    node = malloc(sizeof(table_node_t));
    if (node == NULL)
        return MEMORY_ERR;

    node->word = strdup(word);
    node->next = NULL;

    if (cur)
        cur->next = node;
    else
        hash_table->table[index] = node;

    return OK;
}

// Создание HASH таблицы
int create_hash_table(char *file_name, hash_table_t *hash_table, int *cmp_num)
{
    FILE *file = fopen(file_name, "r");
    char word[LEN];
    int ch;

    hash_table->table = malloc(hash_table->size * sizeof(table_node_t));
    init_hash_table(hash_table);

    while(!feof(file))
    {
        ch = read_string(file, word);

        if (ch != OK)
        {
            fclose(file);
            return ch;
        }

        ch = add_to_hash_table(word, hash_table, cmp_num);
        if (ch != OK)
        {
            fclose(file);
            return ch;
        }
    }

    fclose(file);

    return OK;
}

// Вывод HASH таблицы
void print_hash_table(hash_table_t hash_table)
{
    table_node_t *cur = NULL;

    printf("HASH table:\n");
    for (int i = 0; i < hash_table.size; i++)
    {
        printf("%d: ", i);

        cur = hash_table.table[i];

        if (cur)
        {
            while (cur->next != NULL)
            {
                printf("%s, ", cur->word);
                cur = cur->next;
            }

            printf("%s", cur->word);
        }

        printf("\n");
    }
}

// Поиск в HASH таблице
int find_hash_table(hash_table_t hash_table, char *word, int *cmp_num)
{
    table_node_t *cur;
    int index = hash_function(word, hash_table.size);

    cur = hash_table.table[index];

    if (cur)
    {

        while (cur->next != NULL)
        {
            *cmp_num += 1;
            if (strcmp(cur->word, word) == 0)
                return index;

            cur = cur->next;
        }

        *cmp_num += 1;
        if (strcmp(cur->word, word) == 0)
            return index;
    }

    return -1;
}

// Подсчет количества слов в таблице
static int count_hash_table_words(hash_table_t hash_table)
{
    int count = 0;
    table_node_t *cur;

    for (int i = 0; i < hash_table.size; i++)
    {
        cur = hash_table.table[i];

        while (cur != NULL)
        {
            count++;
            cur = cur->next;
        }
    }

    return count;
}

// Подсчет максимального числа коллизий
int count_collision(hash_table_t hash_table)
{
    int max = 0, count;
    table_node_t *cur;

    for (int i = 0; i < hash_table.size; i++)
    {
        count = 0;
        cur = hash_table.table[i];

        while (cur != NULL)
        {
            count++;
            cur = cur->next;
        }

        if (count > max)
            max = count;
    }

    printf("\nMax number of collisisions: %d\n", max);
    if (max > 3)
        printf("You need to restruct HASH table!\n");

    return max;
}

// Реструктуризация HASH таблицы
hash_table_t restruct_hash_table(hash_table_t hash_table, int new_size)
{
    hash_table_t new_hash_table;
    table_node_t *cur;
    new_hash_table.table = NULL;
    int amount = count_hash_table_words(hash_table);
    char **array = malloc(amount * sizeof(char *));
    int index = 0, cmp_num = 0;

    for (int i = 0; i < hash_table.size; i++)
    {
        cur = hash_table.table[i];

        while (cur != NULL)
        {
            array[index] = strdup(cur->word);
            index++;
            cur = cur->next;
        }
    }

    new_hash_table.table = malloc(new_size * sizeof(table_node_t));
    new_hash_table.size = new_size;
    init_hash_table(&new_hash_table);

    for (int i = 0; i < amount; i++)
        add_to_hash_table(array[i], &new_hash_table, &cmp_num);

    for (int i = 0; i < amount; i++)
        free(array[i]);
    free(array);

    return new_hash_table;
}

// Удаление списка
static void free_list(table_node_t *head)
{
    table_node_t *cur = head;
    table_node_t *next = NULL;

    while (cur != NULL)
    {
        next = cur->next;
        free(cur->word);
        free(cur);
        cur = next;
    }
}

// Удаление HASH таблицы
void free_hash_table(hash_table_t *hash_table)
{
    if (hash_table->table)
    {
        for (int i = 0; i < hash_table->size; i++)
            free_list(hash_table->table[i]);

        free(hash_table->table);
    }
}
