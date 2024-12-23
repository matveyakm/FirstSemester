#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH_OF_LINE 2048

char *getCommentsFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    char *outputComments = malloc(MAX_LENGTH_OF_LINE * 100 * sizeof(char));
    if (!outputComments) {
        fclose(file);
        return NULL;
    }
    outputComments[0] = '\0';

    char line[MAX_LENGTH_OF_LINE];
    while (fgets(line, sizeof(line), file)) {
        char *commentStart = strchr(line, ';');
        if (commentStart) {
            strcat(outputComments, commentStart);
        }
    }

    fclose(file);
    return outputComments;
}

void printCommentsFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        puts("File cant be read.");
        return;
    }

    char line[MAX_LENGTH_OF_LINE];
    while (fgets(line, sizeof(line), file)) {
        char *commentStart = strchr(line, ';');
        if (commentStart) {
            printf("%s", commentStart);
        }
    }

    fclose(file);
}