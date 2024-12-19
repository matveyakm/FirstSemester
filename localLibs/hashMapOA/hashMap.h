#pragma once
#include <stdbool.h>

typedef struct HashMap HashMap;

HashMap *createHashMap(unsigned int size);
void deleteHashMap(HashMap *map);
bool resizeHashMap(HashMap *map, unsigned int newSize);
bool insertIntoHashMap(HashMap *map, char *key, int value);
bool findInHashMap(HashMap *map, char *key, int *outValue);
bool removeFromHashMap(HashMap *map, char *key);
void printHashMap(HashMap *map);
void getStatusOfHashMap(HashMap *map, float *loadFactor, int *maxLengthOfString, float *avgLengthOfString);
