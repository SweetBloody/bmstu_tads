#include <stdio.h>
#include "cdio.h"
#include "const.h"
#include "bin_tree.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "analysis.h"

int main(int argc, char **argv)
{
    int choice = -1, ch, cmp_num = 0, new_size = 0;
    bin_tree_t *bin_tree = NULL;
    avl_tree_t *avl_tree = NULL;
    hash_table_t hash_table;
    hash_table.table = NULL;
    char word[LEN] ;
    setbuf(stdout, NULL);

    if (argc != 2)
    {
        print_errors(INCORRECT_ARGS);
        return INCORRECT_ARGS;
    }

    ch = file_check(argv[1], "r");
    if (ch != OK)
    {
        print_errors(ch);
        return ch;
    }

    while (choice != EXIT)
    {
        choice = print_menu();

        switch (choice)
        {
            case 1:
                bin_tree = create_bin_tree(argv[1], &cmp_num);
                if (bin_tree == NULL)
                {
                    free_bin_tree(bin_tree);
                    free_hash_table(&hash_table);
                    print_errors(MEMORY_ERR);
                    return MEMORY_ERR;
                }
                printf("Bin tree was successfully created!\n\n");


                avl_tree = create_avl_tree(argv[1], &cmp_num);
                if (avl_tree == NULL)
                {
                    free_bin_tree(bin_tree);
                    free_avl_tree(avl_tree);
                    free_hash_table(&hash_table);
                    print_errors(MEMORY_ERR);
                    return MEMORY_ERR;
                }
                printf("AVL tree was successfully created!\n\n");
                break;

            case 2:
                bin_tree_to_dot(bin_tree);
                break;

            case 3:
                avl_tree_to_dot(avl_tree);
                break;

            case 4:
                input_hash_size(&hash_table.size);
                ch = create_hash_table(argv[1], &hash_table, &cmp_num);
                if (ch != OK)
                {
                    free_bin_tree(bin_tree);
                    free_avl_tree(avl_tree);
                    free_hash_table(&hash_table);
                    print_errors(ch);
                    return ch;
                }
                printf("HASH table was successfully created!\n\n");
                break;

            case 5:
                print_hash_table(hash_table);
                count_collision(hash_table);
                break;

            case 6:
                input_hash_size(&new_size);
                hash_table = restruct_hash_table(hash_table, new_size);
                printf("HASH table was successfully restructed!\n\n");
                break;

            case 7:
                input_word(word);

                bin_tree = add_to_bin_tree(word, bin_tree, &cmp_num);
                if (bin_tree == NULL)
                {
                    free_bin_tree(bin_tree);
                    free_avl_tree(avl_tree);
                    free_hash_table(&hash_table);
                    print_errors(MEMORY_ERR);
                    return MEMORY_ERR;
                }

                avl_tree = add_to_avl_tree(word, avl_tree, &cmp_num);
                if (avl_tree == NULL)
                {
                    free_bin_tree(bin_tree);
                    free_avl_tree(avl_tree);
                    free_hash_table(&hash_table);
                    print_errors(MEMORY_ERR);
                    return MEMORY_ERR;
                }

                ch = add_to_hash_table(word, &hash_table, &cmp_num);
                if (ch != OK)
                {
                    free_bin_tree(bin_tree);
                    free_avl_tree(avl_tree);
                    free_hash_table(&hash_table);
                    print_errors(ch);
                    return ch;
                }

                break;

            case 8:
                analysis_cl();
                break;

        }
    }

    free_bin_tree(bin_tree);
    free_avl_tree(avl_tree);
    free_hash_table(&hash_table);

    return OK;
}
