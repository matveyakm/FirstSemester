#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../localLibs/trees/binTree.h"
#include "IOHandler.h"
#include "expressionCalculator.h"
#define MAX_LENGTH_OF_TEST_EXPRESSION 128

static void convertScannedToStringRecursive(char *str, binTreeNode *node) {
    if (node == NULL) {
        return;
    }

    char *dataStr = _nodeToString(getNodeData(node));
    char *dataStrIter = dataStr; 
    while (*dataStrIter) {
        if (strlen(str) + 2 >= MAX_LENGTH_OF_TEST_EXPRESSION) {
            break;
        }
        sprintf(str + strlen(str), "%c", *dataStrIter);
        ++dataStrIter;
    }

    if (strlen(str) + 1 < MAX_LENGTH_OF_TEST_EXPRESSION) {
        sprintf(str + strlen(str), " ");
    }

    free(dataStr);

    convertScannedToStringRecursive(str, getLeftChild(node));
    convertScannedToStringRecursive(str, getRightChild(node));
}

char *getScannedExpression(binTreeNode *node) {
    if (node == NULL) {
        return NULL;
    }
    char *str = malloc(MAX_LENGTH_OF_TEST_EXPRESSION * sizeof(char));
    *str = '\0';
    convertScannedToStringRecursive(str, node);
    return str;
}

bool validationTest(char *testFileName) {
    bool isTestSuccessful = true;
    FILE *globalFile = fopen(testFileName, "r");
    if (globalFile == NULL) {
        return false;
    }

    char line[1024];
    bool isLineWithTrueValue = false;
    int calculatedValue = -1024;
    while (fgets(line, sizeof(line), globalFile)) {
        if (!isLineWithTrueValue) {      
            binTreeNode *root = parseExpression(line);
            calculatedValue = calculateValue(root);
            char *scannedStr = getScannedExpression(root);
            isTestSuccessful *= strcmp(line, scannedStr) == '\n';
            free(scannedStr);
            freeNode(root);
        } else {
            int trueValue;
            sscanf(line, "%d", &trueValue);
            isTestSuccessful *= calculatedValue == trueValue;
        }
        isLineWithTrueValue = !isLineWithTrueValue;
    }
    fclose(globalFile);
    return isTestSuccessful;
}