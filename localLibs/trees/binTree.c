#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binTree.h"

typedef struct binTreeNode {
    void *data;
    struct binTreeNode *left;
    struct binTreeNode *right;
} binTreeNode;

binTreeNode *createNode(void *data) {
    binTreeNode *newNode = malloc(sizeof(binTreeNode));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

void *getNodeData(binTreeNode *node) {
    if (!node) {
        return NULL;
    }
    return node->data;
}

void *changeNodeData(binTreeNode *node, void *newData) {
    if (!node) {
        return NULL;
    }
    void *changingData = node->data;
    node->data = newData;
    return changingData;
}

void setNodeData(binTreeNode *node, void *newData) {
    if (!node) {
        return;
    }
    node->data = newData;
}

void addLeftChild(binTreeNode *node, binTreeNode *child) {
    if (!node || !child || node->left) {
        return;
    }
    node->left = child;
}

void addRightChild(binTreeNode *node, binTreeNode *child) {
    if (!node || !child || node->right) {
        return;
    }
    node->right = child;
}

binTreeNode *getLeftChild(binTreeNode *node) {
    if (!node) {
        return NULL;
    }
    return node->left;
}

binTreeNode *getRightChild(binTreeNode *node) {
    if (!node) {
        return NULL;
    }
    return node->right;
}

void clearNodeRepresent(binTreeNode *node) {
    if (node->left) {
        clearNodeRepresent(node->left);
    }
    if (node->right) {
        clearNodeRepresent(node->right);
    }
    free(node);
}

void freeNode(binTreeNode *node) { // !
    if (node->left) {
        freeNode(node->left);
    }
    if (node->right) {
        freeNode(node->right);
    }
    free(node->data);
    free(node);
}

static void printNodeRecursive(binTreeNode *node, char *(*convertDataToString)(void *), int depth) {
    if (node == NULL) {
        for (int i = 0; i < depth; ++i) printf("    ");
        printf("NULL\n");
        return;
    }

    for (int i = 0; i < depth; ++i) printf("    ");
    char *dataStr = convertDataToString(node->data);
    if (dataStr != NULL) {
        printf("%s\n", dataStr);
        //free(dataStr);
    } else {
        printf("NULL\n");
    }
    printNodeRecursive(node->left, convertDataToString, depth + 1);
    printNodeRecursive(node->right, convertDataToString, depth + 1);
}

void printNode(binTreeNode *node, char *(*convertDataToString)(void *)) {
    if (node == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printNodeRecursive(node, convertDataToString, 0);
}

// BST Utils
typedef enum {
    ADD,
    FIND
} variantOfActionInBST;

static void refillWhileFreing(binTreeNode *root, binTreeNode *node, int (*compare)(void *, void *)) {
    if (!node) return;
    addToBST(root, getNodeData(node), compare);
    refillWhileFreing(root, node->left, compare);
    refillWhileFreing(root, node->right, compare);
    free(node);
}


binTreeNode *interactWithBST(binTreeNode *node, void *data, int (*compare)(void *, void *), variantOfActionInBST action) {
    int resultOfComparing = compare(node->data, data);
    if (resultOfComparing == 0) {
        return node;
    }
    if (resultOfComparing > 0) {
        if (!node->left) {
            if (action == ADD) {
                addLeftChild(node, createNode(data));
                return node->left;
            }
            return node;
        }
        return interactWithBST(node->left, data, compare, action);
    }
    if (resultOfComparing < 0) {
        if (!node->right) {
            if (action == ADD) {
                addRightChild(node, createNode(data));
                return node->right;
            }
            return node;
        }
        return interactWithBST(node->right, data, compare, action);
    }
    return node;
}

binTreeNode *addToBST(binTreeNode *node, void *data, int (*compare)(void *, void *)) {
    if (!data || !node) {
        return NULL;
    }
    return interactWithBST(node, data, compare, ADD);
}

binTreeNode *findInBST(binTreeNode *node, void *data, int (*compare)(void *, void *)) {
    if (!data || !node) {
        return NULL;
    }
    return interactWithBST(node, data, compare, FIND);
}

bool freeFromBST(binTreeNode *node, void *data, int (*compare)(void *, void *)) {
    if (!node || !data) {
        return false;
    }

    // Найти узел для удаления
    binTreeNode *targetNode = interactWithBST(node, data, compare, FIND);
    if (!targetNode) {
        return false; // Узел не найден
    }

    // Если узел - лист
    if (!targetNode->left && !targetNode->right) {
        free(targetNode->data); // Освобождаем память для data
        free(targetNode);      // Удаляем узел
        return true;
    }

    // Если узел имеет только одного потомка
    if (!targetNode->left || !targetNode->right) {
        binTreeNode *child = targetNode->left ? targetNode->left : targetNode->right;
        free(targetNode->data); // Освобождаем память для data
        *targetNode = *child;   // Перемещаем данные и потомки
        free(child);            // Удаляем потомка
        return true;
    }
    // Если узел имеет двух потомков
    // Ищем минимальный узел в правом поддереве
    binTreeNode *minNodeParent = targetNode;
    binTreeNode *minNode = targetNode->right;
    while (minNode->left) {
        minNodeParent = minNode;
        minNode = minNode->left;
    }

    // Заменяем данные удаляемого узла
    free(targetNode->data);      // Освобождаем память текущих данных
    targetNode->data = minNode->data; // Перемещаем указатель на данные из минимального узла
    
    // Удаляем минимальный узел
    if (minNodeParent->left == minNode) {
        minNodeParent->left = minNode->right;
    } else {
        minNodeParent->right = minNode->right;
    }
    free(minNode); // Освобождаем узел (данные уже перемещены)
    return true;
}