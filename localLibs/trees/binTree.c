#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binTree.h"
#include "../list/pointerList.h"

typedef struct binTreeNode {
    void *data;
    struct binTreeNode *left;
    struct binTreeNode *right;
    int balance;
} binTreeNode;

binTreeNode *createNode(void *data) {
    binTreeNode *newNode = malloc(sizeof(binTreeNode));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->balance = 0;
    return newNode;
}

// Small right rotation
binTreeNode *rotateRight(binTreeNode *y) {
    binTreeNode *x = y->left;
    binTreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->balance = (y->right ? y->right->balance : 0) - (y->left ? y->left->balance : 0);
    x->balance = (x->right ? x->right->balance : 0) - (x->left ? x->left->balance : 0);

    return x;
}

// Small left rotation
binTreeNode *rotateLeft(binTreeNode *x) {
    binTreeNode *y = x->right;
    binTreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->balance = (x->right ? x->right->balance : 0) - (x->left ? x->left->balance : 0);
    y->balance = (y->right ? y->right->balance : 0) - (y->left ? y->left->balance : 0);

    return y;
}

// Big right rotation
binTreeNode *rotateLeftRight(binTreeNode *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// Big left rotation
binTreeNode *rotateRightLeft(binTreeNode *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

int getBalance(binTreeNode *node) {
    if (!node) {
        return 0;
    }
    int leftBalance = node->left ? node->left->balance + 1 : 0;
    int rightBalance = node->right ? node->right->balance + 1 : 0;
    return leftBalance - rightBalance;
}

binTreeNode *balanceNode(binTreeNode *node) {
    if (!node) {
        return NULL;
    }

    node->balance = getBalance(node);

    if (node->balance > 1) {
        if (node->left && node->left->balance < 0) {
            return rotateLeftRight(node);
        }
        return rotateRight(node);
    }

    if (node->balance < -1) {
        if (node->right && node->right->balance > 0) {
            return rotateRightLeft(node);
        }
        return rotateLeft(node);
    }

    return node;
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
    --node->balance;
}

void addRightChild(binTreeNode *node, binTreeNode *child) {
    if (!node || !child || node->right) {
        return;
    }
    node->right = child;
    ++node->balance;
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
    if (!node) {
        return;
    }
    if (node->left) {
        freeNode(node->left);
    }
    if (node->right) {
        freeNode(node->right);
    }
    free(node->data);
    free(node);
}

void freeLeftChild(binTreeNode *root) {
    if (root || root->left) {
        freeNode(root->left);
        root->left;
    }
}

void freeRightChild(binTreeNode *root) {
    if (root || root->right) {
        freeNode(root->right);
        root->right;
    }
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
        free(dataStr);
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

static void fillListRecursive(PtrList *list, binTreeNode *node) {
    if (!node) {
        return;
    }
    appendPtr(list, node->data);
    fillListRecursive(list, node->left);
    fillListRecursive(list, node->right);
}

PtrList *binTreeToPtrList(binTreeNode *node) {
    if (node == NULL) {
        return NULL;
    }
    PtrList *list = createPtrList(0);
    fillListRecursive(list, node);
    return list;
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
    if (!node) {
        node = createNode(data);
        return node;
    }
    if (!data) {
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

    binTreeNode *targetNode = interactWithBST(node, data, compare, FIND);
    if (!targetNode) {
        return false;
    }

    if (!targetNode->left && !targetNode->right) {
        free(targetNode->data);
        free(targetNode);      
        return true;
    }

    if (!targetNode->left || !targetNode->right) {
        binTreeNode *child = targetNode->left ? targetNode->left : targetNode->right;
        free(targetNode->data);
        *targetNode = *child;
        free(child);
        return true;
    }

    binTreeNode *minNodeParent = targetNode;
    binTreeNode *minNode = targetNode->right;
    while (minNode->left) {
        minNodeParent = minNode;
        minNode = minNode->left;
    }

    free(targetNode->data);
    targetNode->data = minNode->data;

    if (minNodeParent->left == minNode) {
        minNodeParent->left = minNode->right;
    } else {
        minNodeParent->right = minNode->right;
    }
    free(minNode);
    return true;
}