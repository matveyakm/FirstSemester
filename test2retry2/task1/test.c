#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "list/listDeclaration.h"
#include "oddIndexDeleter.h"

#define TEST_LIST_LENGTH 1024

bool validationTest(int testsLeft) {
    bool isTestSuccessful = true;
    int errorCode = OK;
    
    int *correctResult = malloc((TEST_LIST_LENGTH / 2 + 1) * sizeof(int));
    List *list = createList(0);
    if (!list) {
        return false;
    }

    srand(clock());
    for (int i = 0; i < TEST_LIST_LENGTH; ++i) {
        int value = rand() % 1000;

        if (i % 2 == 0) {
            correctResult[i / 2] = value;
        }

        appendL(list, value, &errorCode);
        if (errorCode == ALLOCATION_ERROR) {
            free(correctResult);
            deleteList(list);
            return false;
        }
    }

    isTestSuccessful *= deleteElementsWithOddIndex(list);

    for (int i = 0; i < getListLength(list); ++i) {
        isTestSuccessful *= peekL(list, i, &errorCode) == correctResult[i];
        if (errorCode == ALLOCATION_ERROR) {
            free(correctResult);
            deleteList(list);
            return false;
        }
    }

    free(correctResult);
    deleteList(list);
    if (testsLeft <= 1) {
        return isTestSuccessful;
    }
    return isTestSuccessful * validationTest(testsLeft - 1);
}