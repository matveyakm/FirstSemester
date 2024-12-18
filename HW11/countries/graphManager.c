#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graphManager.h"

typedef enum {
    NotLinked = -1,
    Capital = -2
} StateStatus;

StateGraph *createStateGraph(int size) {
    StateGraph *graph = malloc(sizeof(StateGraph));
    graph->distMatrix = malloc(size * sizeof(int *));
    graph->status = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        graph->distMatrix[i] = calloc(size, sizeof(int));
        graph->status[i] = NotLinked;
    }
    graph->size = size;
    return graph;
}

void link(StateGraph *graph, int firstTownIndex, int secondTownIndex, unsigned int distance) {
    if (graph && firstTownIndex < graph->size && secondTownIndex < graph->size && firstTownIndex != secondTownIndex) {
        graph->distMatrix[firstTownIndex][secondTownIndex] = (int)distance;
        graph->distMatrix[secondTownIndex][firstTownIndex] =(int)distance;
    }
}

void makeCapital(StateGraph *graph, int townIndex) {
    if (graph) {
        graph->status[townIndex] = Capital;
    }
}

void undoCapital(StateGraph *graph, int townIndex) {
    if (graph && graph->status[townIndex] == Capital) {
        graph->status[townIndex] = NotLinked;
        for (int i = 0; i < graph->size; ++i) {
            if (graph->status[i] == townIndex) {
                graph->status[i] = NotLinked;
            }
        }
    }
}

static bool isGraphCorrect(StateGraph *graph) {
    for (int i = 0; i < graph->size; ++i) {
        int townLinks = 0;
        for (int j = 0; j < graph->size; ++j) {
            townLinks += graph->distMatrix[i][j] != 0;
        }
        if (townLinks == 0) {
            return false;
        }
    }
    return true;
}

static int getFormingStatus(StateGraph *graph) {
    int status = 0;
    int countOfCapitals = 0;
    for (int i = 0; i < graph->size; ++i) {
        status += graph->status[i] == NotLinked;
        countOfCapitals += graph->status[i] == Capital;
    }
    return countOfCapitals == 0 ? -1 : status;
}

void formStates(StateGraph *graph) {
    if (!graph || !isGraphCorrect(graph)) {
        puts("Not correct");
        return;
    }

    int formingStatus = getFormingStatus(graph);
    int townPeekIndex = 0;
    while (formingStatus > 0) {
        if (graph->status[townPeekIndex] != NotLinked) {
            int invadingTownIndex = -1;
            int minDistance = INT_MAX;
            for (int i = 0; i < graph->size; ++i) {
                int dist = graph->distMatrix[i][townPeekIndex];
                if (dist != 0 && graph->status[i] == NotLinked) {
                    if (dist < minDistance) {
                        minDistance = dist;
                        invadingTownIndex = i;
                    }
                }
            }
            if (invadingTownIndex != -1) {
                int newStatus = graph->status[townPeekIndex] == Capital ? townPeekIndex : graph->status[townPeekIndex];
                graph->status[invadingTownIndex] = newStatus;
                --formingStatus;
            }
        }
        townPeekIndex = townPeekIndex + 1 < graph->size ? townPeekIndex + 1 : 0;
    }
}

static int getColor(int colors[], int townIndex, int status) {
    int color;
    switch (status) {
        case NotLinked:
            color = 37;
            break;
        case Capital:
            for (int i = 0; i < 6; ++i) {
                if (colors[i] == townIndex) {
                    color = 41 + i;
                }
            }
            break;
        default:
            for (int i = 0; i < 6; ++i) {
                if (colors[i] == status) {
                    color = 31 + i;
                }
            }
            break;
    }
    return color;
}

static bool isLinkStateforming(StateGraph *graph, int i, int j) {
    if (graph->status[i] == Capital && graph->status[j] == Capital) {
        return false;
    }
    if (graph->status[i] == graph->status[j]) {
        return true;
    }
    if (graph->status[i] == Capital && graph->status[j] == i) {
        return true;
    }
    if (graph->status[j] == Capital && graph->status[i] == j) {
        return true;
    }
    return false;
}

static bool isStatesFormed(StateGraph *graph) {
    for (int i = 0; i < graph->size; ++i) {
        if (graph->status[i] == NotLinked) {
            return false;
        }
    }
    return true;
}

void coloredPrint(StateGraph *graph, int *capitals) {
    printf("[S] ");
    for (int i = 0; i < graph->size; ++i) {
        printf("\033[1;%dm[%d]\033[0m ", getColor(capitals, i, graph->status[i]), i);
    }
    printf("\n");
    for (int i = 0; i < graph->size; ++i) {
        printf("\033[1;%dm[%d]\033[0m ", getColor(capitals, i, graph->status[i]), i);
        for (int j = 0; j < graph->size; ++j) {
            if (graph->distMatrix[i][j] != 0 && isLinkStateforming(graph, i, j)) {
                printf("\033[1;%dm %d \033[0m ", getColor(capitals, i, graph->status[i]), graph->distMatrix[i][j]);
            } else if (i != j){
                printf("\033[0;%dm %d \033[0m ", 37, graph->distMatrix[i][j]);
            } else {
                printf("    ");
            }
            
        }
        printf("\n");
    }

    if (!isStatesFormed(graph)) {
        return;
    }
    int capitalPeeker = 0;
    while (capitals[capitalPeeker] != -1) {
        int color = getColor(capitals, capitals[capitalPeeker], capitals[capitalPeeker]);
        printf("\033[1;%dmState %d: %d\033[0m", color, capitals[capitalPeeker], capitals[capitalPeeker]);
        for (int j = 0; j < graph->size; ++j) {
            if (graph->status[j] == capitals[capitalPeeker]) {
                printf("\033[1;%dm, %d\033[0m", color, j);
            }
        }
        printf("\n");
        ++capitalPeeker;
    }
}

void colorlessPrint(StateGraph *graph, int *capitals) {
    printf("[S] ");
    for (int i = 0; i < graph->size; ++i) {
        if (graph->status[i] == Capital) {
            printf("[X] ");
        } else if (graph->status[i] == NotLinked) {
            printf("[N] ");
        } else {
            printf("[%d] ", graph->status[i]);
        }
    }
    printf("\n[M] ");
    for (int i = 0; i < graph->size; ++i) {
        printf("[%d] ", i);
    }
    printf("\n");
    for (int i = 0; i < graph->size; ++i) {
        printf("[%d] ", i);
        for (int j = 0; j < graph->size; ++j) {
            printf(" %d  ", graph->distMatrix[i][j]);
        }
        printf("\n");
    }

    if (!isStatesFormed(graph)) {
        return;
    }
    int capitalPeeker = 0;
    while (capitals[capitalPeeker] != -1) {
        printf("State %d: %d", capitals[capitalPeeker], capitals[capitalPeeker]);
        for (int j = 0; j < graph->size; ++j) {
            if (graph->status[j] == capitals[capitalPeeker]) {
                printf(", %d", j);
            }
        }
        printf("\n");
        ++capitalPeeker;
    }
}

int *getCapitals(StateGraph *graph, int *countOfCapitals) {
    int *capitals = calloc(graph->size + 1, sizeof(int));
    *countOfCapitals = 0;
    for (int i = 0; i < graph->size; ++i) {
        if (graph->status[i] == Capital) {
            capitals[*countOfCapitals] = i;
            ++(*countOfCapitals);
        }
    }
    for (int i = *countOfCapitals; i < graph->size + 1; ++i) {
        capitals[i] = -1;
    }
    return capitals;
}

void printStates(StateGraph *graph) {
    if (!graph) {
        puts("Graph is damaged.");
    }
    int countOfCapitals = 0;
    int *capitals = getCapitals(graph, &countOfCapitals);
    if (countOfCapitals <= 6) {
        coloredPrint(graph, capitals);
    } else {
        colorlessPrint(graph, capitals);
    }
    free(capitals);
}

void deleteStateGraph(StateGraph *graph) {
    free(graph->status);
    for (int i = 0; i < graph->size; ++i) {
        free(graph->distMatrix[i]);
    }
    free(graph->distMatrix);
    free(graph);
}