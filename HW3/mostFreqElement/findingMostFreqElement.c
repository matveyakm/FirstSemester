#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../localLibs/arrayFuncs/arrayFuncs.h"
#include "../../localLibs/testingTools/testingTools.h"

int linearFindForMostFreqElement(int *array, const int arrayLength) {
    int mostFrequentElement = array[0];
    int maxCounted = 0;
    int currentCountingElement = 0;
    int currentCounted = 0;
    for (int i = 0; i < arrayLength; i++) {
        if (array[i] == currentCountingElement) {
            ++currentCounted;
        }
        if (array[i] != currentCountingElement || i + 1 == arrayLength) {
            if (currentCounted > maxCounted) {
                maxCounted = currentCounted;
                mostFrequentElement = currentCountingElement;
            }
            currentCountingElement = array[i];
            currentCounted = 1;
        }
    }
    return mostFrequentElement;
}

int quadraticFindForMostFreqElement(int *array, const int arrayLength) {
    int mostFrequentElement = 0;
    int maxCounted = 0;
    for (int i = 0; i < arrayLength; i++) {
        int currentCount = 0;
        for (int j = 0; j < arrayLength; j++) {
            currentCount += array[i] == array[j];
        }
        if (currentCount > maxCounted || (currentCount == maxCounted && array[i] < mostFrequentElement)) {
            maxCounted = currentCount;
            mostFrequentElement = array[i];
        }
    }
    return mostFrequentElement;
}

int findForMostFreqElement(int *array, const int arrayLength) {
    if (arrayLength <= 0 || array == NULL) {
        puts("Passed array or pointer is empty!");
        return 0;
    }
    int *arrayCopy = malloc(arrayLength * sizeof(int));
    memcpy(arrayCopy, array, arrayLength * sizeof(int));
    if (!isArraySorted(array, arrayLength)) {
        qsorting(arrayCopy, arrayLength);
    }
    int result = linearFindForMostFreqElement(arrayCopy, arrayLength);
    free(arrayCopy);
    return result;
}

int findForMostFreqElementByCounting(int *array, const int arrayLength) {
    int smallestElementValue = array[0];
    int biggestElementValue = array[0];
    for (int i = 0; i < arrayLength; ++i) {
        if (smallestElementValue > array[i]) {
            smallestElementValue = array[i];
        } else if (biggestElementValue < array[i]) {
            biggestElementValue = array[i];
        }
    }
    int maximumOfElementValueTypes = biggestElementValue - smallestElementValue + 1;
    if (maximumOfElementValueTypes > 1000000) {
        puts("Difference between max element and min element is too big to calculate by counting!");
        return 0;
    }

    int *elementCounter = malloc(maximumOfElementValueTypes * sizeof(int));
    for (int i = 0; i < arrayLength; ++i) {
        ++elementCounter[array[i] - smallestElementValue];
    }
    int countOfMostFreqElement = 0;
    int indexOfMostFreqElement = 0;
    for (int i = 0; i < maximumOfElementValueTypes; i++) {
        if (countOfMostFreqElement < elementCounter[i]) {
            countOfMostFreqElement = elementCounter[i];
            indexOfMostFreqElement = i + smallestElementValue;
        }
    }

    free(elementCounter);
    return indexOfMostFreqElement;
}