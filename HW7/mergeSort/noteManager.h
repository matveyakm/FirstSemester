#pragma once
#include <stdbool.h>
#include "../../localLibs/list/pointerList.h"

typedef struct Note {
    char name[128];
    long phoneNumber;
} Note;

Note *makeNote(char name[], long phoneNumber);
PtrList *loadFromFile(char *fileName, int *maxLengthOfName);
void displayNotes(PtrList *notes, int maxLengthOfName);

int compareNotesByName(void *first, void *second);
int compareNotesByPhoneNumber(void *first, void *second);
