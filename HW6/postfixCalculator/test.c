#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfixCalculator.h"
#include "sortingStation.h"
#include "../../localLibs/stack/stackDeclaration.h"
#include "../../localLibs/queue/queueDeclaration.h"

typedef struct testingElement {
    char infix[128];
    char postfix[128];
    int expressionValue;
} testingElement;


testingElement *loadTestingFile(char *fileName, int *countOfTests) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        puts("Reading failed.");
        return NULL;
    }

    int allocatedElements = 10;
    testingElement *loadedElements = malloc(allocatedElements * sizeof(testingElement));

    size_t readingBufferSize = 128;
    ssize_t bytesRead = 0;
    char *readingBuffer = NULL;

    *countOfTests = 0;
    int countOfStringsRead = 0;

    char infix[128] = " ";
    char postfix[128] = " ";
    int expressionValue;
    while (bytesRead != -1) {
        bytesRead = getline(&readingBuffer, &readingBufferSize, file);
        switch (countOfStringsRead % 3) {
        case 0:
            strncpy(infix, readingBuffer, sizeof(infix));
            infix[bytesRead - 1] = '\0';
            break;
        case 1:
            strncpy(postfix, readingBuffer, sizeof(postfix));
            postfix[bytesRead - 1] = '\0';
            break;
        case 2:
            if (sscanf(readingBuffer, "%d", &expressionValue) == 1) {
                if (*countOfTests >= allocatedElements) {
                    allocatedElements *= 2;
                    testingElement *temp = realloc(loadedElements, allocatedElements * sizeof(testingElement));
                    loadedElements = temp;
                }

                testingElement newElement;
                strncpy(newElement.infix, infix, sizeof(newElement.infix));
                newElement.infix[sizeof(newElement.infix) - 1] = '\0';
                strncpy(newElement.postfix, postfix, sizeof(newElement.postfix));
                newElement.postfix[sizeof(newElement.postfix) - 1] = '\0';
                newElement.expressionValue = expressionValue;

                loadedElements[*countOfTests] = newElement;
                ++(*countOfTests);
            } else {
                printf("===Error parsing line: %s\n", readingBuffer);
            }
            break;
        }
        ++countOfStringsRead;
    }
    free(readingBuffer);
    fclose(file);
    return loadedElements;
}

bool validationTest(char *fileNameOfTestFile) {
    bool isTestSuccesful = true;
    int countOfTests = 0;
    testingElement *tests = loadTestingFile(fileNameOfTestFile, &countOfTests);
    for (int i = 0; i < countOfTests; ++i) {
        printf("started %d (%d) [%s]\n", i, tests[i].expressionValue, tests[i].postfix);
        char *postfixGenerated = postfixExpressionToString(sortingMachine(tests[i].infix));
        int valueCalculatedByString = postfixCalculator(tests[i].postfix);
        int valueCalculatedByQueue = calculator(tests[i].infix);
        if (strcmp(postfixGenerated, tests[i].postfix) != 0 || valueCalculatedByString != tests[i].expressionValue || valueCalculatedByQueue != tests[i].expressionValue) {
            printf("==ER INFIX = %s -=-=-=-=-\n", tests[i].infix);
            printf("==   Generated: %s [Expected: %s]\n", postfixGenerated, tests[i].postfix);
            printf("==   Calculated(str): %d [Expected: %d]\n", valueCalculatedByString, tests[i].expressionValue);
            printf("==   Calculated(que): %d [Expected: %d]\n", valueCalculatedByQueue, tests[i].expressionValue);
            isTestSuccesful = false;
        } else {
            puts("Success.");
        }
    }
    free(tests);
    puts(isTestSuccesful ? "Test successfully passed." : "Test failed.");
    return isTestSuccesful;
}
// (4 * (2 + 3) - (5 / 1))