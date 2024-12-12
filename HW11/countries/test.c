#include <stdio.h>
#include <stdbool.h>
#include "graphManager.h"
#include "fileManager.h"

bool areArraysEqual(int *array1, int *array2, int length) {
    for (int i = 0; i < length; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

bool test1() {
    StateGraph *graph = readGraphFromFile("graphTaskTest1.txt");
    if (!graph) {
        return false;
    }
    formStates(graph);
    int correctResult[] = {1, -2, 1, 1, 6, 1, -2, 1, 1, -2};
    return areArraysEqual(graph->status, correctResult, graph->size);
}

bool test2() {
    StateGraph *graph = readGraphFromFile("graphTaskTest2.txt");
    if (!graph) {
        return false;
    }
    formStates(graph);
    int correctResult[] = {1, -2, 1, 1, 1, -2, 1};
    return areArraysEqual(graph->status, correctResult, graph->size);
}

bool test3() {
    StateGraph *graph = readGraphFromFile("graphTaskTest3.txt");
    if (!graph) {
        return false;
    }
    formStates(graph);
    int correctResult[] = {1, -2, 1, 13, 13, 1, 1, 13, 13, 13, 1, 1, 13, -2, 1, 19, 19, 1, 19, -2, 1, 13, 1, 1, 1, };
    return areArraysEqual(graph->status, correctResult, graph->size);
}

bool validationTest() {
    return test1() && test2() && test3();
}