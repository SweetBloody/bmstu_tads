#ifndef LAB_06_HASH_TABLE_H
#define LAB_06_HASH_TABLE_H

typedef struct table_node_t table_node_t;

typedef struct
{
    table_node_t **table;  // Массив указателей на списки
    int size;              // Размер хэш-таблицы
} hash_table_t;

struct table_node_t
{
    char *word;            // Значение узла списка
    table_node_t *next;    // Указатель на следующий элемент списка
};

// Добавление добавление элемента в HASH таблицу
int add_to_hash_table(char *word, hash_table_t *hash_table, int *cmp_num);

// Создание HASH таблицы
int create_hash_table(char *file_name, hash_table_t *hash_table, int *cmp_num);

// Вывод HASH таблицы
void print_hash_table(hash_table_t hash_table);

// Поиск в HASH таблице
int find_hash_table(hash_table_t hash_table, char *word, int *cmp_num);

// Подсчет максимального числа коллизий
int count_collision(hash_table_t hash_table);

// Реструктуризация HASH таблицы
hash_table_t restruct_hash_table(hash_table_t hash_table, int new_size);

// Удаление HASH таблицы
void free_hash_table(hash_table_t *hash_table);

#endif //LAB_06_HASH_TABLE_H
