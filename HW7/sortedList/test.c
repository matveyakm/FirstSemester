#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../localLibs/testingTools/testingTools.h"
#include "../../localLibs/list/listDeclaration.h"
#include "listManager.h"

bool validationTest(int countOfTests) {
    List *sortedList = createList(0);

    int arrayLength = 2048;
    int *array = malloc(arrayLength * sizeof(int));
    randomizeArray(array, arrayLength, 0);

    for (int i = 0; i < arrayLength; ++i) {
        addValue(sortedList, array[i]);
    }

    int *sortedArray = listToArray(sortedList);
    
    qsorting(array, arrayLength);

    bool isTestSuccesful = isArraySorted(sortedArray, arrayLength) * areArraysEqual(array, sortedArray, arrayLength);
    free(array);

    sortedList = arrayToList(sortedArray, arrayLength);
    int deleteValuesArrayLength = 512;
    int *valueToDelete = malloc(deleteValuesArrayLength * sizeof(int));
    randomizeArray(valueToDelete, deleteValuesArrayLength, 0);

    for (int i = 0; i < deleteValuesArrayLength; ++i) {
        deleteValue(sortedList, valueToDelete[i]);
    }

    free(valueToDelete);
    int newLength = listLength(sortedList);
    sortedArray = listToArray(sortedList);
    isTestSuccesful *= isArraySorted(sortedArray, newLength) * (newLength < arrayLength);

    if (countOfTests == 0) {
        return isTestSuccesful;
    }

    return isTestSuccesful * validationTest(countOfTests - 1);
}