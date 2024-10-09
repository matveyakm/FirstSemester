# Параметры сборки
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
INCLUDE_DIRS = -I/Users/matveyakm/Documents/HW3/mostFreqElement \
                -I/Users/matveyakm/Documents/localLibs/arrayFuncs \
                -I/Users/matveyakm/Documents/localLibs/binSearch \
                -I/Users/matveyakm/Documents/localLibs/bubbleSort \
                -I/Users/matveyakm/Documents/localLibs/insertionSort \
                -I/Users/matveyakm/Documents/localLibs/qsort \
                -I/Users/matveyakm/Documents/localLibs/testingTools

# Определяем параметр TEST для тестирования
ifdef TEST
CFLAGS += -DTEST
endif

# Исходные файлы
SRC = /Users/matveyakm/Documents/HW3/mostFreqElement/main.c \
      /Users/matveyakm/Documents/HW3/mostFreqElement/findingMostFreqElement.c \
      /Users/matveyakm/Documents/HW3/mostFreqElement/test.c \
      /Users/matveyakm/Documents/localLibs/arrayFuncs/arrayFuncs.c \
      /Users/matveyakm/Documents/localLibs/binSearch/binSearch.c \
      /Users/matveyakm/Documents/localLibs/bubbleSort/bubbleSort.c \
      /Users/matveyakm/Documents/localLibs/insertionSort/insertionSort.c \
      /Users/matveyakm/Documents/localLibs/qsort/qsort.c \
      /Users/matveyakm/Documents/localLibs/testingTools/testingTools.c

# Объектные файлы
OBJ = $(SRC:.c=.o)

# Целевой исполняемый файл
TARGET = main

# Правило по умолчанию
all: $(TARGET)

# Линковка
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $^

# Компиляция объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Чистка скомпилированных файлов
clean:
	rm -f $(OBJ) $(TARGET)

# Правила для тестирования
test: CFLAGS += -DTEST
test: $(TARGET)

.PHONY: all clean test
