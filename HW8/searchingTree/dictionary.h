#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

Dictionary *createDictionary();
void addPairToDict(Dictionary *dict, int key, char data[]);
char *getDataByKey(Dictionary *dict, int key);
bool isPairExist(Dictionary *dict, int key);
void clearPair(Dictionary *dict, int key);
void printDictionary(Dictionary *dict);