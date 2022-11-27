#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>
#include <time.h>
#include "analysis.h"
#include "const.h"
#include "cdio.h"

#define N 1000

// Анализ создания бинарного дерева
static double time_bin_create(bin_tree_t **tree, int *cmp_num)
{
    double time = 0;
    clock_t start, stop;

    for (int i = 0; i < N; i++)
    {
        free_bin_tree(*tree);
        start = clock();
        *tree = create_bin_tree("analysis.txt", cmp_num);
        stop = clock();
        time += stop - start;
    }

    *cmp_num /= N;

    return time / N;

}

// Анализ добавления одного слова в бинарное дерево
static long int time_bin_add(bin_tree_t **tree, char *word, int *cmp_num)
{
    struct timespec mt1, mt2;
    long int tt = 0;

    for (int i = 0; i < N; i++)
    {
        free_bin_tree(*tree);
        *tree = create_bin_tree("analysis.txt", cmp_num);
        *cmp_num = 0;
        clock_gettime(CLOCK_REALTIME, &mt1);
        *tree = add_to_bin_tree(word, *tree, cmp_num);
        clock_gettime(CLOCK_REALTIME, &mt2);
        tt += 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    }

    return tt / N;
}

// Анализ создания АВЛ дерева
static double time_avl_create(avl_tree_t **tree, int *cmp_num)
{
    double time = 0;
    clock_t start, stop;

    for (int i = 0; i < N; i++)
    {
        free_avl_tree(*tree);
        start = clock();
        *tree = create_avl_tree("analysis.txt", cmp_num);
        stop = clock();
        time += stop - start;
    }

    *cmp_num /= N;

    return time / N;

}

// Анализ добавления одного слова в АВЛ дерево
static long int time_avl_add(avl_tree_t **tree, char *word, int *cmp_num)
{
    struct timespec mt1, mt2;
    long int tt = 0;

    for (int i = 0; i < N; i++)
    {
        free_avl_tree(*tree);
        *tree = create_avl_tree("analysis.txt", cmp_num);
        *cmp_num = 0;
        clock_gettime(CLOCK_REALTIME, &mt1);
        *tree = add_to_avl_tree(word, *tree, cmp_num);
        clock_gettime(CLOCK_REALTIME, &mt2);
        tt += 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    }

    return tt / N;
}

// Анализ создания HASH таблицы
static double time_hash_create(hash_table_t *hash_table, int *cmp_num)
{
    double time = 0;
    clock_t start, stop;

    for (int i = 0; i < N; i++)
    {
        free_hash_table(hash_table);
        start = clock();
        create_hash_table("analysis.txt", hash_table, cmp_num);
        stop = clock();
        time += stop - start;
    }

    *cmp_num /= N;

    return time / N;
}

// Анализ добавления одного слова в HASH таблицу
static long int time_hash_add(hash_table_t *hash_table, char *word, int *cmp_num)
{
    struct timespec mt1, mt2;
    long int tt = 0;

    for (int i = 0; i < N; i++)
    {
        free_hash_table(hash_table);
        create_hash_table("analysis.txt", hash_table, cmp_num);
        *cmp_num = 0;
        clock_gettime(CLOCK_REALTIME, &mt1);
        add_to_hash_table(word, hash_table, cmp_num);
        clock_gettime(CLOCK_REALTIME, &mt2);
        tt += 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    }

    return tt / N;
}

// Анализ добавления одного слова в файл
static long int time_file_add(char *word)
{
    struct timespec mt1, mt2;
    long int tt = 0;

    for (int i = 0; i < N; i++)
    {
        clock_gettime(CLOCK_REALTIME, &mt1);
        FILE *file = fopen("analysis_out.txt", "a");
        fprintf(file, "%s", word);
        fclose(file);
        clock_gettime(CLOCK_REALTIME, &mt2);
        tt += 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    }

    return tt / N;
}

// Анализ количества сравнений
static void cmp_nums_get(bin_tree_t **bin_tree, avl_tree_t **avl_tree, hash_table_t *hash_table,
                        int *cmp_bin_avg, int *cmp_avl_avg, int *cmp_hash_avg, int amount)
{
    FILE *file;
    char word[LEN];
    int cmp_num = 0;

    free_bin_tree(*bin_tree);
    *bin_tree = create_bin_tree("analysis.txt", &cmp_num);
    free_avl_tree(*avl_tree);
    *avl_tree = create_avl_tree("analysis.txt", &cmp_num);
    free_hash_table(hash_table);
    create_hash_table("analysis.txt", hash_table, &cmp_num);

    file = fopen("analysis.txt", "r");

    for (int i = 0; i < amount; i++)
    {
        fscanf(file, "%s", word);
        find_bin_tree(*bin_tree, word, cmp_bin_avg);
        find_avl_tree(*avl_tree, word, cmp_avl_avg);
        find_hash_table(*hash_table, word, cmp_hash_avg);
    }

    *cmp_bin_avg /= amount;
    *cmp_avl_avg /= amount;
    *cmp_hash_avg /= amount;

    fclose(file);
}

// Анализ
void analysis_cl()
{
    double time_bin_1, time_avl_1, time_hash_1;
    long int time_bin_2, time_avl_2, time_hash_2, time_file;
    int cmp_bin_create = 0, cmp_avl_create = 0, cmp_hash_create = 0;
    int cmp_bin_add = 0, cmp_avl_add = 0, cmp_hash_add = 0;
    int cmp_bin_avg = 0, cmp_avl_avg = 0, cmp_hash_avg = 0;
    bin_tree_t *bin_tree = NULL;
    avl_tree_t *avl_tree = NULL;
    hash_table_t hash_table;
    hash_table.table = NULL;
    int amount = count_words("analysis.txt");
    char word[LEN];

    printf("Amount of words: %d\n", amount);
    input_hash_size(&hash_table.size);

    input_word(word);

    time_bin_1 = time_bin_create(&bin_tree, &cmp_bin_create);
    time_bin_2 = time_bin_add(&bin_tree, word, &cmp_bin_add);
    time_avl_1 = time_avl_create(&avl_tree, &cmp_avl_create);
    time_avl_2 = time_avl_add(&avl_tree, word, &cmp_avl_add);
    time_hash_1 = time_hash_create(&hash_table, &cmp_hash_create);
    time_hash_2 = time_hash_add(&hash_table, word, &cmp_hash_add);
    time_file = time_file_add(word);

    cmp_nums_get(&bin_tree, &avl_tree, &hash_table, &cmp_bin_avg, &cmp_avl_avg, &cmp_hash_avg, amount);

    FILE *filer = fopen("analysis.txt", "r");
    fseek(filer, 0, SEEK_END); // seek to end of file
    int size = ftell(filer);
    fclose(filer);

    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");
    printf("| Structure | Create time, |   Comparisons  | Add time, |  Comparisons | Memory, bytes | Average number |\n");
    printf("|           |      us      | while creating |     ns    | while adding |               | of comparisons |\n");
    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");
    printf("|  bin tree |  %10.6f  |  %8d      | %9ld |  %8d    | %10ld    | %10d     |\n", time_bin_1, cmp_bin_create,
           time_bin_2, cmp_bin_add, amount * sizeof(bin_tree_t), cmp_bin_avg);
    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");
    printf("|  avl tree |  %10.6f  |  %8d      | %9ld |  %8d    | %10ld    | %10d     |\n", time_avl_1, cmp_avl_create,
           time_avl_2, cmp_avl_add, amount * sizeof(avl_tree_t), cmp_avl_avg);
    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");
    printf("| hash table|  %10.6f  |  %8d      | %9ld |  %8d    | %10ld    | %10d     |\n", time_hash_1, cmp_hash_create,
           time_hash_2, cmp_hash_add, amount * sizeof(hash_table_t), cmp_hash_avg);
    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");
    printf("|   file    |      -       |        -       | %9ld |       -      | %10d    |        -       |\n", time_file,
           size);
    printf("|-----------|--------------|----------------|-----------|--------------|---------------|----------------|\n");

    FILE *file = fopen("analysis_out.txt", "w");
    fclose(file);

    free_bin_tree(bin_tree);
    free_avl_tree(avl_tree);
    free_hash_table(&hash_table);
}