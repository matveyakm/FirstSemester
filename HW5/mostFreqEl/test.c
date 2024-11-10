#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../HW3/mostFreqElement/findingMostFreqElement.h"
#include "../../localLibs/testingTools/testingTools.h"
#include "../../localLibs/qsort/qsort.h"
#include "../../localLibs/arrayFuncs/arrayFuncs.h"
#include "../../HW3/mostFreqElement/test.h"
#include "fileReader.h"

void writeArrayToFile(char *fileName, int *array, int arrayLength) {
    FILE *file = fopen(fileName, "w");
    for (int i = 0; i < arrayLength; ++i) {
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);
}


bool fileValidationTest(int countOfTests) {
    bool isTestSuccesful = validationTest(); // prove that funcs finding the most frequent element works correctly
    int arrayLength = 100000;
    int *array = malloc(arrayLength * sizeof(int));
    for (int i = 0; i < countOfTests; ++i) { // prove that fileReader works correctly
        randomizeArray(array, arrayLength, 0);

        writeArrayToFile("testarray.txt", array, arrayLength);

        int *readArray = loadFile("testarray.txt", &arrayLength);
        if (arrayLength != 100000 || !areArraysEqual(array, readArray, arrayLength)) {
            isTestSuccesful = false;
        }
        free(readArray);
    }
    free(array);
    puts(isTestSuccesful ? "Test succesfully passed." : "Test failed.");
    return isTestSuccesful;
}
