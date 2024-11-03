#include <stdio.h>
#include <stdlib.h>
#include "pointerList.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

struct PtrList {
    Node *head;
    int length;
    int type;
};

PtrList *createPtrList(int length) {
    PtrList* list = malloc(sizeof(PtrList));
    list->head = NULL;
    list->length = 0;
    list->type = 5;
    while (list->length < length) {
        appendPtr(list, NULL);
    }
    return list;
}

static Node *createNode(void *data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int ptrListLength(PtrList *list) {
    return list->length;
}

static int convertPosition(int length,int position) {
    return position >= 0 ? position % length : position % length + length;
}

static void sortTwoInts(int *first, int *second) {
    if (first < second) {
        return;
    }
    int temp = *first;
    *first = *second;
    *second = temp;
}

void appendPtr(PtrList *list, void *data) {
    Node *newNode = createNode(data);

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    ++list->length;
}

void pushPtr(PtrList *list, int position, void *data) {
    if (position > list->length) {
        return;
    }
    position = convertPosition(list->length, position);

    Node *newNode = createNode(data);
    if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    ++list->length;
}
void popPtr(PtrList *list) {
    free(turnPopPtr(list));
}
void *turnPopPtr(PtrList *list) {
    if (list->head == NULL) {
        return NULL;
    }

    void *removableNodeValue;
    if (list->head->next == NULL) {
        removableNodeValue = list->head->data;
        free(list->head);
        list->head = NULL;
    } else {
        Node* current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        removableNodeValue = current->next->data;
        free(current->next);
        current->next = NULL;
    }
    --list->length;
    return removableNodeValue;
}

void popAtPtr(PtrList *list, int position) {
    free(turnPopAtPtr(list, position));
}

void *turnPopAtPtr(PtrList *list, int position) {
    if (position >= list->length) {
        return NULL;
    }
    position = convertPosition(list->length, position);

    void *removableNodeValue;
    Node* temp;
    if (position == 0) {
        temp = list->head;
        removableNodeValue = temp->data;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        removableNodeValue = temp->data;
        current->next = temp->next;
        free(temp);
    }
    --list->length;
    return removableNodeValue;
}

void *peekPtr(PtrList *list, int position) {
    if (position >= list->length) {
        return NULL; 
    }
    position = convertPosition(list->length, position);

    Node* current = list->head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->data;
}

void swapPtr(PtrList *list, int firstIndex, int secondIndex) {
    firstIndex = convertPosition(list->length, firstIndex);
    secondIndex = convertPosition(list->length, secondIndex);
    sortTwoInts(&firstIndex, &secondIndex);
    Node *smaller;
    Node *bigger;
    for (int i = 0; i < secondIndex; ++i) {
        bigger = bigger->next;
        if (i == firstIndex) {
            smaller = bigger;
        }
    }
    void *temp = smaller->data;
    smaller->data = bigger->data;
    bigger->data = temp;
}

void **ptrListToArray(PtrList *list) {
    const int length = list->length;
    if (length < 1) {
        return NULL;
    }
    void **array = malloc(length * sizeof(void*));
    for (int i = length - 1; i >= 0; --i) {
        array[i] = turnPopPtr(list);
    }
    deletePtrList(list);
    return array;
}

PtrList *arrayToPtrList(void **array, int arrayLength) {
    PtrList *list = createPtrList(0);
    for (int i = 0; i < arrayLength; ++i) {
        appendPtr(list, array[i]);
    }
    free(array);
    return list;
}
void deletePtrList(PtrList *list) {
    while (list->length > 0) {
        popPtr(list);
    }
    free(list);
}