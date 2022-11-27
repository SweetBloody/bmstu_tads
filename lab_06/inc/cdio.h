#ifndef LAB_06_CDIO_H
#define LAB_06_CDIO_H

// Проверка файла
int file_check(char *filename, char *mode);

// Чтение строки из файла
int read_string(FILE *f, char *string);

// Ввод слова для добавления
void input_word(char *word);

// Ввод размерности HASH таблицы
void input_hash_size(int *size);

// Подсчет количества слов в файле
int count_words(char *file_name);

// Вывод меню
int print_menu();

// Вывод сообщений об ошибках
void print_errors(int ch);

#endif //LAB_06_CDIO_H
