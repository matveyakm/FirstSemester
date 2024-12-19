#include <stdio.h>
#include <stdlib.h>
#include "graphManager.h"

StateGraph *readGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    int n = 0, m = 0;
    fscanf(file, "%d %d", &n, &m);

    StateGraph *graph = createStateGraph(n);

    for (int i = 0; i < m; ++i) {
        int city1, city2;
        unsigned int length;
        fscanf(file, "%d %d %u", &city1, &city2, &length);
        link(graph, city1, city2, length);
    }

    int k = 0;
    fscanf(file, "%d", &k);

    for (int i = 0; i < k; ++i) {
        int capital;
        fscanf(file, "%d", &capital);
        makeCapital(graph, capital);
    }

    fclose(file);
    return graph;
}
