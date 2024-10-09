# Имя исполняемого файла
TARGET = main

# Флаг для тестов, по умолчанию пустой
TEST_FLAGS =

# Если передан параметр TEST=1, добавляем флаг TEST
ifeq ($(TEST), 1)
    TEST_FLAGS = -DTEST
endif

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 $(TEST_FLAGS)

# Файлы исходного кода
SRC = main.c test.c \
    ../../localLibs/arrayFuncs/arrayFuncs.c \
    ../../localLibs/binSearch/binSearch.c \
    ../../localLibs/bubbleSort/bubbleSort.c \
    ../../localLibs/insertionSort/insertionSort.c \
    ../../localLibs/qsort/qsort.c \
    ../../localLibs/testingTools/testingTools.c

# Файлы заголовков
INCLUDES = -I. -I../../localLibs/arrayFuncs -I../../localLibs/binSearch \
    -I../../localLibs/bubbleSort -I../../localLibs/insertionSort \
    -I../../localLibs/qsort -I../../localLibs/testingTools

# Компиляция по умолчанию
all: $(TARGET)

# Правило сборки основного файла
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC)

# Очистка собранных файлов
clean:
	rm -f $(TARGET) 
