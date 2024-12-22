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
SRC = main.c \
      ../../localLibs/queue/queueDeclaration.c

# Файлы заголовков
INCLUDES = -I. \
            -I../../localLibs/queue

# Компиляция по умолчанию
all: $(TARGET)

# Правило сборки основного файла
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC)

# Очистка собранных файлов
clean:
	rm -f $(TARGET)

.PHONY: all clean
