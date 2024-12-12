#include <stdio.h>
#include "graphManager.h"
#include "fileManager.h"

int main() {
    StateGraph *states = createStateGraph(9);
    makeCapital(states, 3);
    makeCapital(states, 2);
    makeCapital(states, 7);
    makeCapital(states, 8);
    link(states, 1, 2, 9);
    link(states, 0, 3, 2);
    link(states, 2, 5, 5);
    link(states, 4, 5, 1);
    link(states, 7, 5, 7);
    link(states, 3, 6, 8);
    link(states, 7, 6, 5);
    link(states, 2, 8, 1);
    formStates(states);
    printStates(states);


    StateGraph *graph = readGraphFromFile("graphTask.txt");
    if (graph == NULL) {
        return 1;
    }
    formStates(graph);
    printStates(graph);
    deleteStateGraph(graph);
}