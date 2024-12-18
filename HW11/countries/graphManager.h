#pragma once

typedef struct StateGraph {
    int **distMatrix;
    int *status;
    int size;
} StateGraph;

StateGraph *createStateGraph(int size);
void link(StateGraph *graph, int firstTownIndex, int secondTownIndex, unsigned int distance);
void makeCapital(StateGraph *graph, int townIndex);
void undoCapital(StateGraph *graph, int townIndex);
void formStates(StateGraph *graph);
void printStates(StateGraph *graph);
void deleteStateGraph(StateGraph *graph);