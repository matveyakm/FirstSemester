#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashMap.h"

typedef struct HashMapEntry {
    char *key;
    int value;
    bool isDeleted;
} HashMapEntry;

struct HashMap {
    HashMapEntry *entries;
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
    if (!map) { // =)
        return NULL;
    }

    map->entries = calloc(initialSize, sizeof(HashMapEntry));
    if (!map->entries) { // =)
        free(map);
        return NULL;
    }

    map->size = initialSize;
    map->count = 0;
    return map;
}

void deleteHashMap(HashMap *map) {
    for (unsigned int i = 0; i < map->size; ++i) {
        if (map->entries[i].key) {
            free(map->entries[i].key);
        }
    }
    free(map->entries);
    free(map);
}

bool findInHashMap(HashMap *map, char *key, int *value) {
    unsigned int index = hashFunction(key, map->size);
    unsigned int startIndex = index;

    while (map->entries[index].key) {
        if (!strcmp(map->entries[index].key, key) && !map->entries[index].isDeleted) {
            *value = map->entries[index].value;
            return true;
        }

        index = (index + 1) % map->size;
        if (index == startIndex) {
            break;
        }
    }
    return false;
}

bool resizeHashMap(HashMap *map, unsigned int newSize) {
    if (newSize <= map->count) {
        return false;
    }

    HashMapEntry *newEntries = calloc(newSize, sizeof(HashMapEntry));
    if (!newEntries) {
        return false;
    }

    // refilling
    for (unsigned int i = 0; i < map->size; ++i) {
        HashMapEntry *entry = &map->entries[i];
        if (entry->key && !entry->isDeleted) {
            unsigned int newIndex = hashFunction(entry->key, newSize);
            while (newEntries[newIndex].key) {
                newIndex = (newIndex + 1) % newSize;
            }
            newEntries[newIndex] = *entry;
        }
    }

    free(map->entries);
    map->entries = newEntries;
    map->size = newSize;

    return true;
}

bool insertIntoHashMap(HashMap *map, char *key, int value) {
    if (map->count >= map->size * 0.75) {
        if (!resizeHashMap(map, map->size * 2)) {
            return false;
        }
    }

    size_t index = hashFunction(key, map->size);
    while (map->entries[index].key) {
        if (!strcmp(map->entries[index].key, key) && !map->entries[index].isDeleted) {
            map->entries[index].value = value;
            return true;
        }
        index = (index + 1) % map->size;
    }

    map->entries[index].key = strdup(key);
    map->entries[index].value = value;
    map->entries[index].isDeleted = false;
    map->count++;
    return true;
}

bool removeFromHashMap(HashMap *map, char *key) {
    unsigned int index = hashFunction(key, map->size);
    unsigned int startIndex = index;

    while (map->entries[index].key) {
        if (!strcmp(map->entries[index].key, key) && !map->entries[index].isDeleted) {
            map->entries[index].isDeleted = true;
            free(map->entries[index].key);
            map->entries[index].key = NULL;
            map->count--;
            return true;
        }

        index = (index + 1) % map->size;
        if (index == startIndex) {
            break;
        }
    }
    return false;
}

void printHashMap(HashMap *map) {
    printf("HashMap size: %d, count: %d\n", map->size, map->count);
    for (unsigned int i = 0; i < map->size; ++i) {
        if (map->entries[i].key && !map->entries[i].isDeleted) {
            printf("[%d]: %s -> %d\n", i, map->entries[i].key, map->entries[i].value);
        } else if (map->entries[i].key && map->entries[i].isDeleted) {
            printf("[%d]: [deleted]\n", i);
        } else {
            printf("[%d]: [empty]\n", i);
        }
    }
}

