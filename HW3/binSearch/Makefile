# Имя исполняемого файла
TARGET = main

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c11

# Определяем параметр TEST для тестирования
ifdef TEST
CFLAGS += -DTEST
endif

# Основные исходные файлы
SRCS = /Users/matveyakm/Documents/HW3/binSearch/main.c \
       /Users/matveyakm/Documents/HW3/binSearch/test.c \
       /Users/matveyakm/Documents/localLibs/arrayFuncs/arrayFuncs.c \
       /Users/matveyakm/Documents/localLibs/binSearch/binSearch.c \
       /Users/matveyakm/Documents/localLibs/bubbleSort/bubbleSort.c \
       /Users/matveyakm/Documents/localLibs/insertionSort/insertionSort.c \
       /Users/matveyakm/Documents/localLibs/qsort/qsort.c \
       /Users/matveyakm/Documents/localLibs/testingTools/testingTools.c

# Заголовочные файлы
INCLUDES = -I/Users/matveyakm/Documents/HW3/binSearch \
           -I/Users/matveyakm/Documents/localLibs/arrayFuncs \
           -I/Users/matveyakm/Documents/localLibs/binSearch \
           -I/Users/matveyakm/Documents/localLibs/bubbleSort \
           -I/Users/matveyakm/Documents/localLibs/insertionSort \
           -I/Users/matveyakm/Documents/localLibs/qsort \
           -I/Users/matveyakm/Documents/localLibs/testingTools

# Объектные файлы (измените расширение .c на .o для каждого исходного файла)
OBJS = $(SRCS:.c=.o)

# Правило по умолчанию для сборки всего проекта
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Правило для компиляции .c файлов в объектные файлы .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
