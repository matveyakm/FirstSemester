#include <stdio.h>
#include <stdlib.h>

int *loadFile(char *fileName, int *length) {
    FILE *file = fopen(fileName, "r");

    int capacity = 512;
    int *readArray = malloc(capacity * sizeof(int));

    size_t readingBufferSize = 512;
    char *readingBuffer = malloc(readingBufferSize * sizeof(char));

    int i = 0;
    int element;
    while (getline(&readingBuffer, &readingBufferSize, file) != -1) {
        if (sscanf(readingBuffer, "%d", &element) == 1) {
            if (capacity <= i) {
                capacity *= 2;
                int *temp = realloc(readArray, capacity * sizeof(int));
                readArray = temp;
            }
            readArray[i] = element;
            ++i;
        } else {
            printf("Error parsing line: %s\n", readingBuffer);
        }
    }

    *length = i;
    fclose(file);
    free(readingBuffer);
    return readArray;
}