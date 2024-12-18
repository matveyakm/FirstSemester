#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../../localLibs/hashMapL/hashMap.h"
#include "textAnalyzer.h"

char *samples[] = {
        "hello",
        "world",
        "this",
        "is",
        "the",
        "test",
        "on",
        "lambo",
        "1234567890",
        "ivanpokhabov",
        "alblack52",
        "laptop",
        "jaba",
        "end",
        "curly",
        "bye",
        "tp",
        "boss"
    };

void generateRandomText(char *fileName, int **correctCount) {
    FILE *file = fopen(fileName, "w");
    int lengthOfSampleArray = sizeof(samples) / sizeof(samples[0]);
    srand(clock());
    int countOfWords = rand() % 2500;
    *correctCount = (int *)calloc(lengthOfSampleArray, sizeof(int));
    for (int i = 0; i < countOfWords; ++i) {
        int indexOfSample = rand() % lengthOfSampleArray;
        ++(*correctCount)[indexOfSample];
        fprintf(file, "%s", samples[indexOfSample]);
        switch (rand() % 30) {
        case 0:
            fprintf(file, ", ");
            break;
        case 1:
            fprintf(file, ". ");
            break;
        case 2:
            fprintf(file, "\n");
            break;
        default:
            fprintf(file, " ");
            break;
        }
    }
    fclose(file);
}

bool validationTest(int countOfTests) {
    char *fileName = "rtestHashMapTask.txt";
    bool isTestSuccessful = true;
    int *correctCount;
    generateRandomText(fileName, &correctCount);
    HashMap *map = countWordFrequencies(fileName);
    int lengthOfSampleArray = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < lengthOfSampleArray; ++i) {
        int count = 0;
        findInHashMap(map, samples[i], &count);
        if (count != correctCount[i]) {
            printf("%s %d %d\n", samples[i], count, correctCount[i]);
            isTestSuccessful = false;
        }
    }

    free(correctCount);
    deleteHashMap(map);

    if (countOfTests <= 1) {
        return isTestSuccessful;
    }
    return validationTest(countOfTests - 1) * isTestSuccessful;
}