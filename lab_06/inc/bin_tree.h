#ifndef LAB_06_BIN_TREE_H
#define LAB_06_BIN_TREE_H

typedef struct bin_tree_t bin_tree_t;

struct bin_tree_t
{
    char *word;          // Значение узла дерева
    bin_tree_t *left;    // Указатель на левое поддерево
    bin_tree_t *right;   // Указатель на правое поддерево
};

// Добавление узла в ДДП дерево
bin_tree_t *add_to_bin_tree(char *word, bin_tree_t *tree, int *cmp_num);

// Создание ДДП дерева
bin_tree_t *create_bin_tree(char *file_name, int *cmp_num);

// Поиск в ДДП дереве
bin_tree_t *find_bin_tree(bin_tree_t *tree, char *word, int *cmp_num);

// Удаление бинарного дерева
void free_bin_tree(bin_tree_t *tree);

// Экспорт дерева в DOT формат
void bin_tree_to_dot(bin_tree_t *tree);

#endif //LAB_06_BIN_TREE_H
