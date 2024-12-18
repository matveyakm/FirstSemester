#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../localLibs/hashMapL/hashMap.h"

void cleanWord(char *word) {
    char *source = word, *destination = word;
    while (*source) {
        if (isalnum((unsigned char)*source)) {
            *destination++ = tolower((unsigned char)*source);
        }
        ++source;
    }
    *destination = '\0';
}

void addWord(HashMap *map, char *word) {
    int count;
    bool isWordCountedBefore = findInHashMap(map, word, &count);
    if (isWordCountedBefore) {
        insertIntoHashMap(map, word, count + 1);
    } else {
        insertIntoHashMap(map, word, 1);
    }
}

HashMap *countWordFrequencies(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    HashMap *wordMap = createHashMap(12);
    if (!wordMap) {
        perror("Failed to create HashMap");
        fclose(file);
        return NULL;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " \t\n"); // parsing a line to words
        while (token) {
            cleanWord(token); // ignoring punctuation marks and special characters
            if (strlen(token) > 0) {
                addWord(wordMap, token);
            }
            token = strtok(NULL, " \t\n"); // going next
        }
    }

    fclose(file);
    return wordMap;
}

void printWordFrequencies(char *fileName) {
    HashMap *map = countWordFrequencies(fileName);
    printHashMap(map);
    deleteHashMap(map);
}