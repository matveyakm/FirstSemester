#pragma once
#include <stdio.h>
#include <stdlib.h>
#define PTRLIST_INCLUDED

typedef struct BinTree BinTree;

BinTree *createBinTree();
void addLeftChild(void *data);
void addRightChild(void *data);
void *peekLeftChild();
void *peekRightChild();