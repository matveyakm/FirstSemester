#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct binTreeNode binTreeNode;

binTreeNode *createNode(void *data );
void *getNodeData(binTreeNode *node);
void *changeNodeData(binTreeNode *node, void *newData);
void setNodeData(binTreeNode *node, void *data);
void addLeftChild(binTreeNode *node, binTreeNode *child);
void addRightChild(binTreeNode *node, binTreeNode *child);
binTreeNode *getLeftChild(binTreeNode *node);
binTreeNode *getRightChild(binTreeNode *node);
void clearNodeRepresent(binTreeNode *node);
void freeNode(binTreeNode *node);
void printNode(binTreeNode *node, char *(*convertDataToString)(void *));

// BST Utils
binTreeNode *addToBST(binTreeNode *node, void *data, int (*compare)(void *, void *));
binTreeNode *findInBST(binTreeNode *node, void *data, int (*compare)(void *, void *));
bool freeFromBST(binTreeNode *node, void *data, int (*compare)(void *, void *));