#include "../list/pointerList.h"
#include "../list/pointerList_internal.h"

Node* merge(Node *left, Node *right, int (*compare)(void *, void *)) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (compare(left->data, right->data) <= 0) {
        left->next = merge(left->next, right, compare);
        return left;
    } else {
        right->next = merge(left, right->next, compare);
        return right;
    }
}

void split(Node *source, PtrList *front, PtrList *back) {
    Node *slow = source;
    Node *fast = source->next;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    front->head = source;
    back->head = slow->next;
    slow->next = NULL;
}

void mergeSort(PtrList *list, int (*compare)(void *, void *)) {
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }

    PtrList left = {NULL, 0, 5};
    PtrList right = {NULL, 0, 5};

    split(list->head, &left, &right);

    mergeSort(&left, compare);
    mergeSort(&right, compare);

    list->head = merge(left.head, right.head, compare);
}