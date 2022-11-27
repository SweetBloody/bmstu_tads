#ifndef LAB_06_AVL_TREE_H
#define LAB_06_AVL_TREE_H

typedef struct avl_tree_t avl_tree_t;

struct avl_tree_t
{
    char *word;          // Значение узла дерева
    int height;          // Значение высоты дерева
    avl_tree_t *left;    // Указатель на левое поддерево
    avl_tree_t *right;   // Указатель на правое поддерево
};

// Добавление узла в АВЛ дерево
avl_tree_t *add_to_avl_tree(char *word, avl_tree_t *tree, int *cmp_num);

// Создание АВЛ дерева
avl_tree_t *create_avl_tree(char *file_name, int *cmp_num);

// Поиск в АВЛ дереве
avl_tree_t *find_avl_tree(avl_tree_t *tree, char *word, int *cmp_num);

// Удаление АВЛ дерева
void free_avl_tree(avl_tree_t *tree);

// Экспорт дерева в DOT формат
void avl_tree_to_dot(avl_tree_t *tree);

#endif //LAB_06_AVL_TREE_H
