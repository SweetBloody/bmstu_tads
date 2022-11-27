#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"
#include "const.h"
#include "cdio.h"

// Вспомогательная функция для высоты
static int height(avl_tree_t *tree)
{
    if (tree)
        return tree->height;
    else
        return 0;
}

// Вычисление balance factor для заданного узла
static int balance_factor(avl_tree_t *tree)
{
    return height(tree->right) - height(tree->left);
}

// Задаем корректное значение height для заданного узла
static void correct_height(avl_tree_t *tree)
{
    int left_height, right_height;

    left_height = height(tree->left);
    right_height = height(tree->right);

    if (left_height > right_height)
        tree->height = left_height + 1;
    else
        tree->height = right_height + 1;
}

// Левый поворот
static avl_tree_t *rotate_left(avl_tree_t *tree)
{
    avl_tree_t *tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    correct_height(tree);
    correct_height(tmp);

    return tmp;
}

// Правый поворот
static avl_tree_t *rotate_right(avl_tree_t *tree)
{
    avl_tree_t *tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    correct_height(tree);
    correct_height(tmp);

    return tmp;
}

// Балансировка узла АВЛ
static avl_tree_t *balance(avl_tree_t *tree)
{
    correct_height(tree);

    if (balance_factor(tree) > 1)
    {
        if (balance_factor(tree->right) < 0)
            tree->right = rotate_right(tree->right);

        return rotate_left(tree);
    }
    if (balance_factor(tree) < -1)
    {
        if (balance_factor(tree->left) > 0)
            tree->left = rotate_left(tree->left);

        return rotate_right(tree);
    }

    return tree;
}

// Добавление узла в АВЛ дерево
avl_tree_t *add_to_avl_tree(char *word, avl_tree_t *tree, int *cmp_num)
{
    avl_tree_t *tmp = NULL;

    if (tree == NULL)
    {
        tmp = malloc(sizeof(avl_tree_t));
        if (tmp == NULL)
            return NULL;

        tmp->word = strdup(word);
        tmp->height = 1;
        tmp->left = NULL;
        tmp->right = NULL;

        return tmp;
    }
    else if (strcmp(word, tree->word) < 0)
    {
        tree->left = add_to_avl_tree(word, tree->left, cmp_num);
        *cmp_num += 1;
    }
    else if (strcmp(word, tree->word) > 0)
    {
        tree->right = add_to_avl_tree(word, tree->right, cmp_num);
        *cmp_num += 1;
    }

    return balance(tree);
}

// Создание АВЛ дерева
avl_tree_t *create_avl_tree(char *file_name, int *cmp_num)
{
    avl_tree_t *tree = NULL;
    FILE *file = fopen(file_name, "r");
    char word[LEN];
    int ch;

    while(!feof(file))
    {
        ch = read_string(file, word);
        if (ch != OK)
        {
            fclose(file);
            return NULL;
        }

        tree = add_to_avl_tree(word, tree, cmp_num);
        if (tree == NULL)
        {
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    return tree;
}

// Поиск в АВЛ дереве
avl_tree_t *find_avl_tree(avl_tree_t *tree, char *word, int *cmp_num)
{
    avl_tree_t *res = NULL;

    if (strcmp(tree->word, word) == 0)
    {
        *cmp_num += 1;
        res = tree;
    }
    else if (strcmp(word, tree->word) < 0)
    {
        *cmp_num += 1;
        res = find_avl_tree(tree->left, word, cmp_num);
    }
    else if (strcmp(word, tree->word) > 0)
    {
        *cmp_num += 1;
        res = find_avl_tree(tree->right, word, cmp_num);
    }

    return res;
}

// Удаление АВЛ дерева
void free_avl_tree(avl_tree_t *tree)
{
    if (tree != NULL)
    {
        free_avl_tree(tree->left);
        free_avl_tree(tree->right);
        free(tree->word);
        free(tree);
    }
}

// Обход дерева с записью в DOT
static void print_to_dot(FILE *file, avl_tree_t *tree)
{
    if (tree != NULL)
    {
        if (tree->left != NULL)
            fprintf(file, "%s -- %s;\n", tree->word, tree->left->word);

        if (tree->right != NULL)
            fprintf(file, "%s -- %s;\n", tree->word, tree->right->word);

        print_to_dot(file, tree->left);
        print_to_dot(file, tree->right);
    }
}

// Экспорт дерева в DOT формат
void avl_tree_to_dot(avl_tree_t *tree)
{
    FILE *file = fopen("avl_tree.gv", "w");

    fprintf(file, "graph graph_test {\n");

    print_to_dot(file, tree);

    fprintf(file, "}\n");
    fclose(file);

    printf("AVL tree was successfully exported to DOT file!\n\n");

}