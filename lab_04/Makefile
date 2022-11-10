## Компилятор
CC := gcc

## Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Iinc -ggdb

## Общие объектные файлы программы
OBJS_MAIN := cdio.o analysis.o process.o

app.exe : main.o $(OBJS_MAIN)
	$(CC) -o $@ $^

main.o : src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

cdio.o : src/cdio.c inc/cdio.h
	$(CC) $(CFLAGS) -c src/cdio.c -o $@

analysis.o : src/analysis.c inc/analysis.h
	$(CC) $(CFLAGS) -c src/analysis.c -o $@

process.o : src/process.c inc/process.h
	$(CC) $(CFLAGS) -c src/process.c -o $@

.PHONY : clean
clean :
	rm *.o *.exe