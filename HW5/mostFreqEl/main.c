#include <stdio.h>
#include <stdlib.h>
#include "../../HW3/mostFreqElement/findingMostFreqElement.h"
#include "../../localLibs/testingTools/testingTools.h"

int *loadFile(char *fileName, int *length) {
    FILE *file = fopen(fileName, "r");

    int *readArray = malloc(sizeof(int));

    size_t readingBufferSize = 512;
    char *readingBuffer = NULL;

    int i = 0;
    int element;
    while (getline(&readingBuffer, &readingBufferSize, file) != -1) {
        if (sscanf(readingBuffer, "%d", &element) == 2) {
            readArray[i] = element;
            ++i;
        } else {
            printf("Error parsing line: %s\n", readingBuffer);
        }
    }

    *length = i;
    fclose(file);
    return readArray;
}

int main() {
    int arrayLength;
    int *array = loadFile("array.txt", &arrayLength);
    
    printArray(array, arrayLength);

    findForMostFreqElement(array, arrayLength);

    printArray(array, arrayLength);
    free(array);
}