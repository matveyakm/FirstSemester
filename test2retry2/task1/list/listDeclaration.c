#include <stdio.h>
#include <stdlib.h>
#include "listDeclaration.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct List {
    Node *head;
    Node *tail;
    int length;
};

List *createList(int length) {
    List* list = malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    int errorCode = -1;
    while (list->length < length) {
        appendL(list, 0, &errorCode);
        if (errorCode != OK) {
            deleteList(list);
            return NULL;
        }
    }
    return list;
}

static Node *createNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int getListLength(List *list) {
    if (!list) {
        return -1;
    }
    return list->length;
}

static int convertPosition(int length, int position) {
    return position >= 0 ? position % length : position % length + length;
}

void appendL(List *list, int value, int *errorCode) {
    *errorCode = OK;
    Node *newNode = createNode(value);
    if (!newNode) {
        *errorCode = ALLOCATION_ERROR;
        return;
    }
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    ++list->length;
}

void addL(List *list, int position, int value, int *errorCode) {
    *errorCode = OK;
    if (!list) {
        *errorCode = NULL_POINTER_PASSED;
        return;
    }
    if (position < 0 || position > list->length) {
        *errorCode = OUT_OF_LENGTH;
        return;
    }
    position = convertPosition(list->length, position);

    Node *newNode = createNode(value);
    if (!newNode) {
        *errorCode = ALLOCATION_ERROR;
        return;
    }


    if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
        if (list->length == 0) {
            list->tail = newNode;
        }
    } else if (position == list->length) {
        appendL(list, value, errorCode);
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

int popL(List *list, int *errorCode) {
    *errorCode = OK;
    if (!list) {
        *errorCode = NULL_POINTER_PASSED;
        return 0;
    }
    if (!list->head) {
        *errorCode = OUT_OF_LENGTH;
        return 0;
    }

    int removableNodeValue = -1;
    if (list->head == list->tail) {
        removableNodeValue = list->head->value;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *current = list->head;
        while (current->next != list->tail) {
            current = current->next;
        }
        removableNodeValue = list->tail->value;
        free(list->tail);
        current->next = NULL;
        list->tail = current;
    }
    --list->length;
    return removableNodeValue;
}

int popAtL(List *list, int position, int *errorCode) {
    *errorCode = OK;
    if (!list) {
        *errorCode = NULL_POINTER_PASSED;
        return 0;
    }
    if (!list->head) {
        *errorCode = OUT_OF_LENGTH;
        return 0;
    }
    if (position < 0 || position >= list->length) {
        *errorCode = OUT_OF_LENGTH;
        return 0;
    }
    position = convertPosition(list->length, position);

    int removableNodeValue = 0;
    Node *temp;
    if (position == 0) {
        temp = list->head;
        removableNodeValue = temp->value;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
        free(temp);
    } else {
        Node *current = list->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        removableNodeValue = temp->value;
        current->next = temp->next;
        if (temp == list->tail) {
            list->tail = current;
        }
        free(temp);
    }
    --list->length;
    return removableNodeValue;
}

int peekL(List *list, int position, int *errorCode) {
    *errorCode = OK;
    if (!list) {
        *errorCode = NULL_POINTER_PASSED;
        return 0;
    }
    if (!list->head) {
        *errorCode = OUT_OF_LENGTH;
        return 0;
    }
    if (position < 0 || position >= list->length) {
        *errorCode = OUT_OF_LENGTH;
        return 0;
    }
    position = convertPosition(list->length, position);

    Node* current = list->head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->value;
}

void printList(List *list) {
    if (!list) {
        puts("Passed pointer equals NULL.");
        return;
    }
    if (list->head == NULL) {
        puts("[]");
        return;
    }
    printf("[");
    Node *current = list->head;
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int *copyListIntoArray(List *list) {
    const int length = list->length;
    if (!list || length < 1) {
        return NULL;
    }
    int *array = malloc(length * sizeof(int));
    if (!array) {
        return NULL;
    }

    Node *current = list->head;
    for (int i = 0; i < length; ++i) {
        array[i] = current->value;
        current = current->next;
    }
    return array;
}

List *copyArrayIntoList(int *array, int arrayLength) {
    List *list = createList(0);
    if (!list) {
        return NULL;
    }
    int errorCode = OK;
    for (int i = 0; i < arrayLength; ++i) {
        appendL(list, array[i], &errorCode);
        if (errorCode == ALLOCATION_ERROR) {
            deleteList(list);
            return NULL;
        }
    }
    return list;
}

void deleteList(List *list) {
    if (!list) {
        return;
    }

    while (list->head) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    free(list);
}