#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fileManager.h"
#include "list/listDeclaration.h"

int processFile(const char *inputFile, const char *outputFile, int a, int b) {
    if (a > b) {
        return VALUES_IS_NOT_CORRECT;
    }

    FILE *f = fopen(inputFile, "r");
    if (!f) {
        return INPUTFILE_NOT_FOUND;
    }

    List *lessThanA = createList(0);
    List *betweenAAndB = createList(0);
    List *greaterThanB = createList(0);

    int value = -191;
    while (fscanf(f, "%d", &value) != EOF) {
        if (value < a) {
            appendL(lessThanA, value);
        } else if (value <= b) {
            appendL(betweenAAndB, value);
        } else {
            appendL(greaterThanB, value);
        }
    }
    fclose(f);

    FILE *g = fopen(outputFile, "w");
    if (!g) {
        deleteList(lessThanA);
        deleteList(betweenAAndB);
        deleteList(greaterThanB);
        return OUTPUTFILE_NOT_FOUND;
    }

    for (int i = 0; i < listLength(lessThanA); i++) {
        fprintf(g, "%d ", peekL(lessThanA, i));
    }
    for (int i = 0; i < listLength(betweenAAndB); i++) {
        fprintf(g, "%d ", peekL(betweenAAndB, i));
    }
    for (int i = 0; i < listLength(greaterThanB); i++) {
        fprintf(g, "%d ", peekL(greaterThanB, i));
    }

    fclose(g);

    deleteList(lessThanA);
    deleteList(betweenAAndB);
    deleteList(greaterThanB);
    return OK;
}
