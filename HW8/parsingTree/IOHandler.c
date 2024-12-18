#include <stdio.h>
#include <string.h>
#include "../../localLibs/trees/binTree.h"
#include "../../localLibs/list/pointerList.h"
#define ADDING -1
#define SUBSTRACTION -2
#define PRODUCT -3
#define DIVISION -4

static bool insertTokenRecursive(binTreeNode **node, int *token) {
    if (!*node) {
        *node = createNode(token);
    } else if (*(int *)getNodeData(*node) < 0) { 
        binTreeNode *left = getLeftChild(*node);
        binTreeNode *right = getRightChild(*node);
        if (!left) {
            addLeftChild(*node, createNode(token));
        } else {
            if (!insertTokenRecursive(&left, token)) {
                if (!right) {
                    addRightChild(*node, createNode(token));
                    return true;
                }
                return insertTokenRecursive(&right, token);
            }
        }
    } else {
        return false;
    }
    return true;
}

static void insertToken(binTreeNode **root, char *token) {
    int *inttok = malloc(sizeof(int));
    switch (*token) {
    case '+':
        *inttok = ADDING;
        break;
    case '*':
        *inttok = PRODUCT;
        break;
    case '/':
        *inttok = DIVISION;
        break;
    default:
        *inttok = strcmp(token, "-") == 0 ? SUBSTRACTION : atoi(token);
        break;
    }
    insertTokenRecursive(root, inttok); 
}

binTreeNode *parseExpression(char *expression) {
    binTreeNode *root = NULL;
    char *dupExpression = strdup(expression);
    char *token = strtok(dupExpression, " \t\n");
    while (token) {
        if (strlen(token) > 0 && *token != '(' && *token != ')') {
            insertToken(&root, token);
        }
        token = strtok(NULL, " \t\n");
    }
    free(token);
    free(dupExpression);
    return root;
}

char *_nodeToString(void *data) {
    int maxLengthOfToken = 128;
    char *token = malloc(maxLengthOfToken * sizeof(char));
    switch (*(int *)data) {
    case ADDING:
        strcpy(token, "+");
        break;
    case SUBSTRACTION:
        strcpy(token, "-");
        break;
    case PRODUCT:
        strcpy(token, "*");
        break;
    case DIVISION:
        strcpy(token, "/");
        break;
    default:
        sprintf(token, "%d", *(int *)data);
        break;
    }
    return token;
}

static void printNodeInLineRecursive(binTreeNode *node, char *(*convertDataToString)(void *)) {
    if (node == NULL) {
        return;
    }

    char *dataStr = convertDataToString(getNodeData(node));
    if (dataStr != NULL) {
        printf("%s ", dataStr);
        free(dataStr);
    } else {
        printf("N ");
    }
    printNodeInLineRecursive(getLeftChild(node), convertDataToString);
    printNodeInLineRecursive(getRightChild(node), convertDataToString);
}

void printNodeInLine(binTreeNode *node, char *(*convertDataToString)(void *)) {
    if (node == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printNodeInLineRecursive(node, convertDataToString);
    printf("\n");
}

void printExpression(binTreeNode *root) {
    printNodeInLine(root, _nodeToString);
}