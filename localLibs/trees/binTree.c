#pragma once

typedef struct Node {
    void *data;
    struct Node *left;
    struct Node *right;
} Node;

struct BinTree {
    Node *head;
    int length;
    int type;
};

BinTree *createBinTree() {
    BinTree* tree = malloc(sizeof(BinTree));
    tree->head = NULL;
    tree->length = 0;
    tree->type = 6;
    return tree;
}

static Node *createNode(void *data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

int binTreeLength(BinTree *tree) {
    return tree->length;
}

static int convertPosition(int length,int position) {
    return position >= 0 ? position % length : position % length + length;
}

static void sortTwoInts(int *first, int *second) {
    if (*first <= *second) {
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

    Node *smaller = list->head;
    Node *bigger = list->head;
    for (int i = 0; i < secondIndex; ++i) {
        if (i == firstIndex) {
            smaller = bigger;
        }
        bigger = bigger->next;
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

PtrList *representPtrList(PtrList *initialList) {
    PtrList *copyList = createPtrList(initialList->length);
    Node *initialNode = initialList->head;
    Node *copyNode = copyList->head;
    for (int i = 0; i < initialList->length; ++i) {
        copyNode->data = initialNode->data;
        initialNode = initialNode->next;
        copyNode = copyNode->next;
    }
    return copyList;
}

void deletePtrList(PtrList *list) {
    while (list->length > 0) {
        popPtr(list);
    }
    free(list);
}