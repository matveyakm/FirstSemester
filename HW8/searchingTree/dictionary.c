#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "../../localLibs/trees/binTree.h"
#include "../../localLibs/list/pointerList.h"

struct Dictionary {
    binTreeNode *root;
};

struct Pair {
    int key;
    char *data;
};

Dictionary *createDictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->root = NULL;
    return dict;
}

static Pair *makePair(int key, char *data) {
    char *dataOnHeap = malloc(strlen(data) * sizeof(char));
    strcpy(dataOnHeap, data);

    Pair *pair = malloc(sizeof(Pair));
    pair->data = dataOnHeap;
    pair->key = key;
    return pair;
}

int comparePairs(void *a, void *b) {
    Pair *pairA = (Pair *)a;
    Pair *pairB = (Pair *)b;
    return pairA->key - pairB->key;
}

void addPairToDict(Dictionary *dict, int key, char data[]) {
    Pair *pair = makePair(key, data);
    if (!dict->root) {
        dict->root = createNode(pair);
    } else {
        addToBST(dict->root, pair, comparePairs);
    }
}

char *getDataByKey(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, "");
    Pair *pair = (Pair *)getNodeData(findInBST(dict->root, pattern, comparePairs));
    free(pattern);
    return pair == NULL ? "null" : pair->data;
}

bool isPairExist(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, "");
    bool res = findInBST(dict->root, pattern, comparePairs) != NULL;
    free(pattern);
    return res;
}

void clearPair(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, "");
    freeFromBST(dict->root, pattern, comparePairs);
    free(pattern);
}

void printPair(Pair *pair) {
    printf("[%d: %s]\n", pair->key, pair->data);
}

void printDictionary(Dictionary *dict) {
    PtrList *list = binTreeToPtrList(dict->root);
    for (int i = 0; i < ptrListLength(list); ++i) {
        Pair *pair = (Pair *)peekPtr(list, i);
        printPair(pair);
    } 
    free(list);
}

void deleteDictionary(Dictionary *dict) {
    freeNode(dict->root);
    free(dict);
}