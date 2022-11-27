#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin_tree.h"
#include "const.h"
#include "cdio.h"



// Добавление узла в ДДП дерево
bin_tree_t *add_to_bin_tree(char *word, bin_tree_t *tree, int *cmp_num)
{
    if (tree == NULL)
    {
        tree = malloc(sizeof(bin_tree_t));
        if (tree == NULL)
            return NULL;

        tree->word = strdup(word);
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (strcmp(word, tree->word) < 0)
    {
        tree->left = add_to_bin_tree(word, tree->left, cmp_num);
        *cmp_num += 1;
    }
    else if (strcmp(word, tree->word) > 0)
    {
        tree->right = add_to_bin_tree(word, tree->right, cmp_num);
        *cmp_num += 1;
    }

    return tree;
}

// Создание ДДП дерева
bin_tree_t *create_bin_tree(char *file_name, int *cmp_num)
{
    bin_tree_t *tree = NULL;
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

        tree = add_to_bin_tree(word, tree, cmp_num);
        if (tree == NULL)
        {
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    return tree;
}

// Поиск в ДДП дереве
bin_tree_t *find_bin_tree(bin_tree_t *tree, char *word, int *cmp_num)
{
    bin_tree_t *res = NULL;

    if (strcmp(tree->word, word) == 0)
    {
        *cmp_num += 1;
        res = tree;
    }
    else if (strcmp(word, tree->word) < 0)
    {
        *cmp_num += 1;
        res = find_bin_tree(tree->left, word, cmp_num);
    }
    else if (strcmp(word, tree->word) > 0)
    {
        *cmp_num += 1;
        res = find_bin_tree(tree->right, word, cmp_num);
    }

    return res;
}

// Удаление бинарного дерева
void free_bin_tree(bin_tree_t *tree)
{
    if (tree != NULL)
    {
        free_bin_tree(tree->left);
        free_bin_tree(tree->right);
        free(tree->word);
        free(tree);
    }
}

// Обход дерева с записью в DOT
static void print_to_dot(FILE *file, bin_tree_t *tree)
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
void bin_tree_to_dot(bin_tree_t *tree)
{
    FILE *file = fopen("bin_tree.gv", "w");

    fprintf(file, "graph graph_test {\n");

    print_to_dot(file, tree);

    fprintf(file, "}\n");
    fclose(file);

    printf("Bin tree was successfully exported to DOT file!\n\n");
}