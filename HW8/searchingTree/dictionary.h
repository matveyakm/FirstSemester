#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;
typedef struct Pair Pair;

Dictionary *createDictionary(void);
void addPairToDict(Dictionary *dict, int key, char data[]);
char *getDataByKey(Dictionary *dict, int key);
bool isPairExist(Dictionary *dict, int key);
void clearPair(Dictionary *dict, int key);
void printPair(Pair *pair);
void printDictionary(Dictionary *dict);
void deleteDictionary(Dictionary *dict);