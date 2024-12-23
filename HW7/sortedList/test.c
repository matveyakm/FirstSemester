#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../localLibs/testingTools/testingTools.h"
#include "list/listDeclaration.h"

#define LENGTH 2048

bool validationTest(int countOfTests) {
    SortedList *sortedList = createSortedList(LENGTH);
    if (!sortedList) {
        return false;
    }

    int arrayLength = LENGTH;
    int *array = malloc(arrayLength * sizeof(int));

    // ADDING TEST
    randomizeArray(array, arrayLength, 0);
    for (int i = 0; i < arrayLength; ++i) {
        addValue(sortedList, array[i]);
    }

    int *sortedArray = copySortedListIntoArray(sortedList, &arrayLength);
    
    qsorting(array, arrayLength);

    bool isTestSuccesful = isArraySorted(sortedArray, arrayLength) * areArraysEqual(array, sortedArray, arrayLength);
    free(array);

    // DELETING TEST
    int deleteValuesArrayLength = LENGTH / 3;
    int *valueToDelete = malloc(deleteValuesArrayLength * sizeof(int));
    randomizeArray(valueToDelete, deleteValuesArrayLength, 0);

    for (int i = 0; i < deleteValuesArrayLength; ++i) {
        deleteValue(sortedList, valueToDelete[i]);
    }

    free(valueToDelete);
    int newLength = -1 ;
    sortedArray = copySortedListIntoArray(sortedList, &newLength);
    isTestSuccesful *= isArraySorted(sortedArray, newLength) * (newLength <= arrayLength);

    free(sortedArray);

    if (countOfTests == 0) {
        return isTestSuccesful;
    }
    return isTestSuccesful * validationTest(countOfTests - 1);
}