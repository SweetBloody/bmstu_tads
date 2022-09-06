#include <stdio.h>
#include "const.h"

// Проверка файла
int file_check(char *file_name)
{
    FILE *f = fopen(file_name, "r");

    if (f == NULL)
        return FILE_OPEN_ERR;

    if (ferror(f) != 0)
        return FILE_ERR;

    if (fclose(f) == EOF)
        return FILE_CLOSE_ERR;

    return OK;
}
