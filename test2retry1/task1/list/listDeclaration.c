#include <stdio.h>
#include <stdlib.h>
#include "listDeclaration.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct List {
    Node *head;
    int length;
};

List *createList(int length) {
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->length = 0;
    while (list->length < length) {
        appendL(list, 0);
    }
    return list;
}

static Node *createNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int listLength(List *list) {
    return list->length;
}

static int convertPosition(int length, int position) {
    return position >= 0 ? position % length : position % length + length;
}

void appendL(List *list, int value) {
    Node *newNode = createNode(value);

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

void addL(List *list, int position, int value) {
    if (position > list->length) {
        return;
    }
    position = convertPosition(list->length, position);

    Node *newNode = createNode(value);
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

int popL(List *list) {
    if (list->head == NULL) {
        return -1;
    }

    int removableNodeValue;
    if (list->head->next == NULL) {
        removableNodeValue = list->head->value;
        free(list->head);
        list->head = NULL;
    } else {
        Node* current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        removableNodeValue = current->next->value;
        free(current->next);
        current->next = NULL;
    }
    --list->length;
    return removableNodeValue;
}

int popAtL(List *list, int position) {
    if (position >= list->length) {
        return -1;
    }
    position = convertPosition(list->length, position);

    int removableNodeValue;
    Node* temp;
    if (position == 0) {
        temp = list->head;
        removableNodeValue = temp->value;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        temp = current->next;
        removableNodeValue = temp->value;
        current->next = temp->next;
        free(temp);
    }
    --list->length;
    return removableNodeValue;
}

int peekL(List *list, int position) {
    if (position >= list->length) {
        return -1; 
    }
    position = convertPosition(list->length, position);

    Node* current = list->head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->value;
}

void printList(List *list) {
    if (list->length < 1) {
        puts("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < list->length - 1; ++i) {
        printf("%d, ", peekL(list, i));
    }
    printf("%d]\n", peekL(list, list->length - 1));
}

int *listToArray(List *list) {
    const int length = list->length;
    if (length < 1) {
        return NULL;
    }
    int *array = malloc(length * sizeof(int));
    for (int i = length - 1; i >= 0; --i) {
        array[i] = popL(list);
    }
    deleteList(list);
    return array;
}

List *arrayToList(int *array, int arrayLength) {
    List *list = createList(0);
    for (int i = 0; i < arrayLength; ++i) {
        appendL(list, array[i]);
    }
    free(array);
    return list;
}

void deleteList(List *list) {
    while (list->length > 0) {
        popL(list);
    }
    free(list);
}