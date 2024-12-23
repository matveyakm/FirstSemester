#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listDeclaration.h"

struct SortedList {
    int *data;
    int length;
    int capacity;
};

SortedList *createSortedList(int capacity) {
    SortedList *list = malloc(sizeof(SortedList));
    if (!list) {
        return NULL;
    }
    list->data = malloc(capacity * sizeof(int));
    list->length = 0;
    list->capacity = capacity;
    return list;
}

int getSortedListLength(SortedList *list) {
    if(!list) {
        return -1;
    }
    return list->length;
}

void resizeList(SortedList *list) {
    list->capacity *= 2;
    list->data = realloc(list->data, list->capacity * sizeof(int));
}

void addValue(SortedList *list, int value) {
    if (list->length == list->capacity) {
        resizeList(list);
    }

    int left = 0;
    int right = list->length;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (list->data[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    for (int i = list->length; i > left; --i) {
        list->data[i] = list->data[i - 1];
    }

    list->data[left] = value;
    ++list->length;
}

bool deleteValue(SortedList *list, int value) {
    int left = 0;
    int right = list->length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (list->data[mid] == value) {
            for (int i = mid; i < list->length - 1; ++i) {
                list->data[i] = list->data[i + 1];
            }
            --list->length;
            return true;
        } else if (list->data[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

void deleteSortedList(SortedList *list) {
    if (!list) {
        return;
    }
    if (list->data) {
        free(list->data);
    }
    free(list);
}

int *copySortedListIntoArray(SortedList *list, int *size) {
    if (!list) {
        *size = -1;
        return NULL;
    }
    *size = list->length;
    int *array = malloc(*size * sizeof(int));
    memcpy(array, list->data, *size * sizeof(int));
    return list->data;
}

SortedList *copyArrayIntoSortedList(int *array, int size) {
    if (!array) {
        return NULL;
    }
    SortedList *list = createSortedList(size);
    memcpy(list->data, array, size * sizeof(int));
    return list;
}

void printSortedList(SortedList *list) {
    printf("[");
    for (int i = 0; i < list->length; ++i) {
        printf("%d", list->data[i]);
        if (i < list->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
