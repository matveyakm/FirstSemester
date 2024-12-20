#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "fileManager.h"
#include "list/listDeclaration.h"

bool fillTestFile(const char *fileName, List *numbers) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        return false;
    }
    srand(clock());
    for (int i = 0; i < listLength(numbers); ++i) {
        fprintf(file, "%d ", peekL(numbers, i));
    }
    fclose(file);
    return true;
}

List *generateRandomList(int size) {
    List *list = createList(0);
    srand(clock());
    for (int i = 0; i < size; ++i) {
        appendL(list, rand() % 1000);
    }
    return list;
}

typedef enum {
    beforeA = 0,
    beforeB = 1,
    afterB = 2
} CurrentArea;

bool isValueInArea(int value, int a, int b, CurrentArea currentArea) {
    if (value < a) {
        if (currentArea != beforeA) {
            return false;
        }
    } else if (value <= b) {
        if (currentArea != beforeB) {
            return false;
        }

    } else {
        if (currentArea != afterB) {
            return false;
        }
    }
    return true;
}

bool checkOrder(List *numbers, int value, int a, int b, CurrentArea currentArea) {
    int i = 0;
    while (i < listLength(numbers)) {
        int currentElement = peekL(numbers, i);
        if (isValueInArea(currentElement, a, b, currentArea)) {
            if (currentElement == value) {
                popAtL(numbers, i);
                return true;
            } else {
                return false;
            }
        }
        ++i;
    }
    return false;
}

bool isFileCorrectlyFilled(List *numbers, char *filename, int a, int b) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return false;
    }

    CurrentArea currentArea = beforeA;

    int value = -199;
    while (fscanf(file, "%d", &value) != EOF) {
        if (!isValueInArea(value, a, b, currentArea)) {
            currentArea++;
        }
        if (currentArea > 2) {
            fclose(file);
            return false;
        }
        if (!checkOrder(numbers, value, a, b, currentArea)) {
            fclose(file);
            return false;
        }
    }
    return true;
}

bool validationTest(void) {
    bool isTestSuccessful = true;
    char f[] = "f_test_file.txt";
    char g[] = "g_test_file.txt";

    List *numbers = generateRandomList(1000);
    srand(clock());
    int a = rand() % 800;
    int b = a + rand() % 195;

    if (!fillTestFile(f, numbers)) {
        deleteList(numbers);
        remove(f);
        remove(g);
        return false;
    }

    int errorCode = processFile(f, g, a, b);
    if (errorCode != OK || !isFileCorrectlyFilled(numbers, g, a, b)) {
        isTestSuccessful = false;
    }

    remove(f);
    remove(g);
    deleteList(numbers);
    return isTestSuccessful;
}
