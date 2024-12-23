#include <stdlib.h>
#include <stdbool.h>
#include "selectionSort.h"
#include "../../localLibs/arrayFuncs/arrayFuncs.h"
#include "../../localLibs/testingTools/testingTools.h"

bool checkSpecialCases(void) {
    return !selectionSort(NULL, 52) && !selectionSort(NULL, -1);
}

bool compareWithPrefilled(void) {
    int array[] = {-1, 5, -2, 41, 4, -321, 4};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    selectionSort(array, arrayLength);
    int correctResult[] = {-321, -2, -1, 4, 4, 5, 41};
    for (int i = 0; i < arrayLength; ++i) {
        if(array[i] != correctResult[i]) {
            return false;
        }
    }
    return true;
}

static bool validationTestRecursive(int testsLeft) {
    int arrayLength = 2048;
    int *array = malloc(arrayLength * sizeof(int));
    randomizeArray(array, arrayLength, 0);

    selectionSort(array, arrayLength);

    bool isTestSuccessful = isArraySorted(array, arrayLength);
    
    free(array);
    if (testsLeft == 0) {
        return isTestSuccessful;
    }
    return isTestSuccessful * validationTestRecursive(testsLeft - 1);
}

bool validationTest(int testsLeft) {
    return checkSpecialCases() && compareWithPrefilled() && validationTestRecursive(testsLeft);
}