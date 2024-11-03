#include <stdio.h>
#include <stdlib.h>
#include "cyclicList.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct Cyclic {
    Node *head;
    int length;
    int type;
};

Cyclic *createCyclic(int length) {
    Cyclic* cyclic = malloc(sizeof(Cyclic));
    cyclic->head = NULL;
    cyclic->length = 0;
    cyclic->type = 4;
    while (cyclic->length < length) {
        appendC(cyclic, 0);
    }
    return cyclic;
}

static Node *createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int cyclicLength(Cyclic *cyclic) {
    return cyclic->length;
}

void appendC(Cyclic *cyclic, int value) {
    Node *newNode = createNode(value);

    if (cyclic->head == NULL) {
        cyclic->head = newNode;
    } else {
        Node* current = cyclic->head;
        while (current->next != cyclic->head) {
            current = current->next;
        }
        current->next = newNode;
    }
    newNode->next = cyclic->head;
    ++cyclic->length;
}

static int convertPosition(int length,int position) {
    return position >= 0 ? position % length : position % length + length;
}

void pushAtC(Cyclic *cyclic, int position, int value) {
    position = convertPosition(cyclic->length, position);

    Node *newNode = createNode(value);
    Node *current = cyclic->head;
    if (position == 0) {
        for (int i = 0; i < cyclic->length; ++i) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = cyclic->head;
        cyclic->head = newNode;
    } else {
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    ++cyclic->length;
}

int popC(Cyclic *cyclic) {
    if (cyclic->head == NULL) {
        return -1;
    }

    int removableNodeValue;
    if (cyclic->head->next == cyclic->head) {
        removableNodeValue = cyclic->head->value;
        free(cyclic->head);
        cyclic->head = NULL;
    } else {
        Node *current = cyclic->head;
        while (current->next->next != cyclic->head) {
            current = current->next;
        }
        removableNodeValue = current->next->value;
        free(current->next);
        current->next = cyclic->head;
    }
    --cyclic->length;
    return removableNodeValue;
}

int popAtC(Cyclic *cyclic, int position) {
    position = convertPosition(cyclic->length, position);

    int removableNodeValue;
    Node* temp;
    if (position == 0) {
        temp = cyclic->head;
        removableNodeValue = temp->value;
        cyclic->head = cyclic->head->next;
        free(temp);
    } else {
        Node *current = cyclic->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        removableNodeValue = temp->value;
        current->next = temp->next;
        free(temp);
    }
    --cyclic->length;
    return removableNodeValue;
}

int peekAtC(Cyclic *cyclic, int position) {
    position = convertPosition(cyclic->length, position);

    Node *current = cyclic->head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->value;
}

void shiftHead(Cyclic *cyclic, int shift) {
    shift = convertPosition(cyclic->length, shift);
    Node *current = cyclic->head;
    for (int i = 0; i < shift; ++i) {
        current = current->next;
    }
    cyclic->head = current;
}

void printCyclic(Cyclic *cyclic) {
    if (cyclic->length < 1) {
        puts("[]");
        return;
    }
    printf("[.. , ");
    for (int i = 0; i < cyclic->length - 1; ++i) {
        printf("%d, ", peekAtC(cyclic, i));
    }
    printf("%d, ..]\n", peekAtC(cyclic, cyclic->length - 1));
}

int *cyclicToArray(Cyclic *cyclic) {
    const int length = cyclic->length;
    if (length < 1) {
        return NULL;
    }
    int *array = malloc(length * sizeof(int));
    for (int i = length - 1; i >= 0; --i) {
        array[i] = popC(cyclic);
    }
    deleteCyclic(cyclic);
    return array;
}

Cyclic *arrayToCyclic(int *array, int arrayLength) {
    Cyclic *cyclic = createCyclic(0);
    for (int i = 0; i < arrayLength; ++i) {
        appendC(cyclic, array[i]);
    }
    free(array);
    return cyclic;
}

void deleteCyclic(Cyclic *cyclic) {
    while (cyclic->length > 0) {
        popC(cyclic);
    }
    free(cyclic);
}