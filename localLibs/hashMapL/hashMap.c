#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../list/pointerList.h"
#include "hashMap.h"

typedef struct HashMapEntry {
    char *key;
    int value;
} HashMapEntry;

struct HashMap {
    PtrList **buckets;
    unsigned int size;
    unsigned int count;
};

static unsigned int hashFunction(char *key, unsigned int tableSize) { //
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key++) % tableSize;
    }
    return hash;
}

HashMap *createHashMap(unsigned int initialSize) {
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }

    map->buckets = malloc(sizeof(PtrList *) * initialSize);
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    for (unsigned int i = 0; i < initialSize; ++i) {
        map->buckets[i] = createPtrList(0);
    }

    map->size = initialSize;
    map->count = 0;
    return map;
}

void deleteHashMap(HashMap *map) {
    if (!map) {
        return;
    }

    for (unsigned int i = 0; i < map->size; ++i) {
        PtrList *bucket = map->buckets[i];
        for (int j = 0; j < ptrListLength(bucket); ++j) {
            HashMapEntry *entry = peekPtr(bucket, j);
            free(entry->key);
        }
        deletePtrList(bucket);
    }
    free(map->buckets);
    free(map);
}

bool resizeHashMap(HashMap *map, unsigned int newSize) {
    if (newSize < map->count * 1.2) {
        return false;
    }

    PtrList **newBuckets = malloc(sizeof(PtrList *) * newSize);
    if (!newBuckets) {
        return false;
    }

    for (unsigned int i = 0; i < newSize; ++i) {
        newBuckets[i] = createPtrList(0);
        if (!newBuckets[i]) {
            for (unsigned int j = 0; j < i; ++j) {
                deletePtrList(newBuckets[j]);
            }
            free(newBuckets);
            return false;
        }
    }

    for (unsigned int i = 0; i < map->size; ++i) {
        PtrList *oldBucket = map->buckets[i];
        for (int j = 0; j < ptrListLength(oldBucket); ++j) {
            HashMapEntry *entry = peekPtr(oldBucket, j);
            if (entry) {
                unsigned int newIndex = hashFunction(entry->key, newSize);
                appendPtr(newBuckets[newIndex], entry);
            }
        }
        free(oldBucket);
    }
    free(map->buckets);
    map->buckets = newBuckets;
    map->size = newSize;
    return true;
}


bool insertIntoHashMap(HashMap *map, char *key, int value) {
    if (map->size == 0) {
        resizeHashMap(map, 5);
    }
    while (map->count >= map->size * 0.8) {
        resizeHashMap(map, map->size * 2);
    }

    if (!map) {
        return false;
    }

    unsigned int index = hashFunction(key, map->size);
    PtrList *bucket = map->buckets[index];

    for (int i = 0; i < ptrListLength(bucket); ++i) {
        HashMapEntry *entry = peekPtr(bucket, i);
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return true;
        }
    }

    HashMapEntry *newEntry = malloc(sizeof(HashMapEntry));
    if (!newEntry) {
        return false;
    }

    newEntry->key = strdup(key);
    newEntry->value = value;

    appendPtr(bucket, newEntry);
    map->count++;
    return true;
}

bool findInHashMap(HashMap *map, char *key, int *value) {
    unsigned int index = hashFunction(key, map->size);
    PtrList *bucket = map->buckets[index];

    for (int i = 0; i < ptrListLength(bucket); ++i) {
        HashMapEntry *entry = peekPtr(bucket, i);
        if (strcmp(entry->key, key) == 0) {
            *value = entry->value;
            return true;
        }
    }
    return false;
}

bool removeFromHashMap(HashMap *map, char *key) {
    unsigned int index = hashFunction(key, map->size);
    PtrList *bucket = map->buckets[index];

    for (int i = 0; i < ptrListLength(bucket); ++i) {
        HashMapEntry *entry = peekPtr(bucket, i);
        if (strcmp(entry->key, key) == 0) {
            free(entry->key);
            popAtPtr(bucket, i);
            map->count--;
            return true;
        }
    }
    return false;
}

void printHashMap(HashMap *map) {
    if (!map) {
        puts("Map is damaged.");
        return;
    }

    printf("HashMap. [Size: %d, Count: %d]\n", map->size, map->count);
    for (unsigned int i = 0; i < map->size; ++i) {
        PtrList *bucket = map->buckets[i];
        if (bucket && ptrListLength(bucket) > 0) {
            for (int j = 0; j < ptrListLength(bucket); ++j) {
                HashMapEntry *entry = peekPtr(bucket, j);
                printf("[%d] %s -> %d\n", i, entry->key, entry->value);
            }
        }
    }

    int maxLen;
    float lF, avgLen;
    getStatusOfHashMap(map, &lF, &maxLen, &avgLen);
    printf("[%.2f | %d | %.2f]\n", lF, maxLen, avgLen);
}

void getStatusOfHashMap(HashMap *map, float *loadFactor, int *maxLengthOfString, float *avgLengthOfString) {
    if (!map) {
        *loadFactor = -1.0;
        *maxLengthOfString = -1;
        *avgLengthOfString = -1.0;
    }

    if (map->count == 0) {
        *loadFactor = 0.0;
        *maxLengthOfString = 0;
        *avgLengthOfString = 0.0;
    }

    *loadFactor = (float)map->count / map->size;
    *maxLengthOfString = 0;
    unsigned int sumOfLengths = 0;
    for (unsigned int i = 0; i < map->size; ++i) {
        PtrList *bucket = map->buckets[i];
        for (int j = 0; j < ptrListLength(bucket); ++j) {
            HashMapEntry *entry = peekPtr(bucket, j);
            int entryLength = strlen(entry->key);
            sumOfLengths += entryLength;
            if (*maxLengthOfString < entryLength) {
                *maxLengthOfString = entryLength;
            }
        }
    }
    *avgLengthOfString = (float)sumOfLengths / map->count;
}