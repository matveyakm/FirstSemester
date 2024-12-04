#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../list/pointerList.h"

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
// clears only a pointer but not the memory
void freeNode(binTreeNode *node);
// frees memory than clears the pointer
void printNode(binTreeNode *node, char *(*convertDataToString)(void *));
// function you passing must copy pointed content even if content has char* type
PtrList *binTreeToPtrList(binTreeNode *node);

// BST Utils
binTreeNode *addToBST(binTreeNode *node, void *data, int (*compare)(void *, void *));
// returns node of added node
binTreeNode *findInBST(binTreeNode *node, void *data, int (*compare)(void *, void *));
bool freeFromBST(binTreeNode *node, void *data, int (*compare)(void *, void *));