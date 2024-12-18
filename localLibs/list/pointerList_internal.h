#pragma once
#include "pointerList.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

struct PtrList {
    Node *head;
    int length;
};