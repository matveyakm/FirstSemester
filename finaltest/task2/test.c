#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

void initializeSeed(int seed) {
    if (seed == 0) {
        srand(clock()); 
    } else {
        srand(seed);
    }
}

void fillRandomArray(int *array, int arrayLength, int low, int high) {
    int rangeСoefficient = high - low + 1;
    for (int i = 0; i < arrayLength; i++) {
        array[i] = rand() % rangeСoefficient + low;
    }
}

void randomizeArray(int *array, int arrayLength, int seed) {
    initializeSeed(seed);
    fillRandomArray(array, arrayLength, -1000, 1000);
}

bool compareWithPrefilled(void) {
    bool isTestSuccessful = true;
    Queue *queue = createQueue();
    int errorCode = 0;

    enqueue(queue, 10, &errorCode);
    isTestSuccessful *= errorCode == OK;

    enqueue(queue, 20, &errorCode);
    isTestSuccessful *= errorCode == OK;

    enqueue(queue, 30, &errorCode);
    isTestSuccessful *= errorCode == OK;

    isTestSuccessful *= dequeue(queue, &errorCode) == 10;
    isTestSuccessful *= errorCode == OK;

    isTestSuccessful *= peekQueue(queue, &errorCode) == 20;
    isTestSuccessful *= errorCode == OK;

    isTestSuccessful *= dequeue(queue, &errorCode) == 20;
    isTestSuccessful *= errorCode == OK;

    enqueue(queue, 40, &errorCode);
    isTestSuccessful *= errorCode == OK;

    isTestSuccessful *= dequeue(queue, &errorCode) == 30;
    isTestSuccessful *= errorCode == OK;

    isTestSuccessful *= dequeue(queue, &errorCode) == 40;
    isTestSuccessful *= errorCode == OK;
    
    dequeue(queue, &errorCode);
    isTestSuccessful *= errorCode == QUEUE_IS_EMPTY;

    freeQueue(queue, &errorCode);
    return isTestSuccessful;
}

bool validationTest(void) {
    bool isTestSuccessful = compareWithPrefilled();
    Queue *queue = createQueue();
    int errorCode = 0;

    int arrayLength = 50;
    int *randomArray = malloc(arrayLength * sizeof(int));
    randomizeArray(randomArray, arrayLength, 0);
    for (int i = 0; i < arrayLength; ++i) {
        enqueue(queue, randomArray[i], &errorCode);
        isTestSuccessful *= errorCode == OK;
    }

    for (int i = 0; i < arrayLength; ++i) {
        isTestSuccessful *= dequeue(queue, &errorCode) == randomArray[i];
        isTestSuccessful *= errorCode == OK;
    }

    free(randomArray);
    freeQueue(queue, &errorCode);
    return isTestSuccessful;
}