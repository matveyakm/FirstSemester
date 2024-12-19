#include <stdio.h>
#include <string.h>
#include "../../localLibs/trees/binTree.h"
#include "../../localLibs/list/pointerList.h"
#ifndef ADDING
#define ADDING -1
#define SUBSTRACTION -2
#define PRODUCT -3
#define DIVISION -4
#endif

int calculateValue(binTreeNode *node) {
    int value = 0;
    if (!node) {
        return value;
    }
    int data = *(int *)getNodeData(node);
    if (isLeaf(node)) {
        return data;
    } else {
        switch (data) {
        case ADDING:
            return calculateValue(getLeftChild(node)) + calculateValue(getRightChild(node));
            break;
        case SUBSTRACTION:
            return calculateValue(getLeftChild(node)) - calculateValue(getRightChild(node));
            break;
        case PRODUCT:
            return calculateValue(getLeftChild(node)) * calculateValue(getRightChild(node));
            break;
        case DIVISION:
            return calculateValue(getLeftChild(node)) / calculateValue(getRightChild(node));
            break;
        default:
            return -1;
            break;
        }
    }
    return 0;
}