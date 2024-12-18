#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../localLibs/queue/queueDeclaration.h"

typedef struct Graph {
    int **matrix;
    int size;
} Graph;

Graph *readGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    Graph *graph = malloc(sizeof(Graph));
    graph->size = size;
    graph->matrix = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        graph->matrix[i] = malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &graph->matrix[i][j]);
        }
    }

    fclose(file);
    return graph;
}

void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->size; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

void bfs(Graph *graph, int startVertex) {
    int size = graph->size;
    bool *visited = calloc(size, sizeof(bool));
    Queue *queue = createQueue();

    enqueue(queue, startVertex);
    visited[startVertex] = true;

    printf("Обход в ширину: ");
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        for (int i = 0; i < size; i++) {
            if (graph->matrix[current][i] && !visited[i]) {
                enqueue(queue, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");

    clearQueue(queue);
    free(visited);
}

bool validationTest(void) { // compare with pre-filled
    const char *filename = "graphTestFTest.txt";
    Graph *graph = readGraphFromFile(filename);

    int startVertex = 0;
    bfs(graph, startVertex); ///

    freeGraph(graph);
}

int main() {
    const char *filename = "graphTaskFTest.txt";
    Graph *graph = readGraphFromFile(filename);

    if (!graph) {
        return 1;
    }

    int startVertex = 0;
    bfs(graph, startVertex);

    freeGraph(graph);
}