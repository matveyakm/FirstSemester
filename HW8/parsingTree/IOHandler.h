#pragma once
#include "../../localLibs/trees/binTree.h"

binTreeNode *parseExpression(char *expression);
void printExpression(binTreeNode *root);
char *_nodeToString(void *data);
