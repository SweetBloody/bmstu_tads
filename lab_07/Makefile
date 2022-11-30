## Компилятор
CC := gcc

## Расположение исходных файлов
SRC := src

## Расположение объектных файлов
OUT := out

## Расположение заголовочных файлов
INC := inc

## Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb -I inc

## Общие объектные файлы программы
OBJS_MAIN := $(OUT)/cdio.o $(OUT)/graph_matrix.o $(OUT)/analysis.o

app.exe : $(OUT)/main.o $(OBJS_MAIN)
		$(CC) -o $@ $^

$(OUT)/%.o : $(SRC)/%.c
		mkdir -p $(OUT)
		$(CC) $(CFLAGS) -c $^ -o $@

.PHONY : clean
clean :
	rm $(OUT)/*.o *.exe