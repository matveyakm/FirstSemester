#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "../../localLibs/trees/binTree.h"
#include "../../localLibs/list/pointerList.h"

struct Dictionary {
    binTreeNode *root;
};

typedef struct Pair {
    int key;
    char *data;
} Pair;

Dictionary *createDictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->root = NULL;
    return dict;
}

static Pair *makePair(int key, char data[]) {
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
    addToBST(dict->root, pair, comparePairs);
}

char *getDataByKey(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, ""); // free?
    Pair *pair = getNodeData(findInBST(dict->root, pattern, comparePairs));
    return pair->data;
}

bool isPairExist(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, ""); // free?
    return findInBST(dict->root, pattern, comparePairs) != NULL;
}

void clearPair(Dictionary *dict, int key) {
    Pair *pattern = makePair(key, ""); // free?
    freeFromBST(dict->root, pattern, comparePairs);
}

char *convertPair(void *rawPair) {
    Pair *pair = (Pair *)rawPair;
    return pair->data;
}

void printDictionary(Dictionary *dict) {
    /*
    PtrList *list = binTreeToPtrList(dict->root);
    printf("62LD: %d\n", ptrListLength(list));
    for (int i = 0; i < ptrListLength(list); ++i) {
        Pair *pair = (Pair *)peekPtr(list, i);
        printf("[%d: %s]\n", pair->key, pair->data);
    } */
   printNode(dict->root, convertPair);
}