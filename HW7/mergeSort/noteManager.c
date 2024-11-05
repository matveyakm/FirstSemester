#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "noteManager.h"
#include "../../localLibs/list/pointerList.h"

Note *makeNote(char name[], long phoneNumber) {
    Note *res = malloc(sizeof(Note));
    strncpy(res->name, name, sizeof(res->name) - 1);
    res->phoneNumber = phoneNumber;
    return res;
}

PtrList *loadFromFile(char *fileName, int *maxLengthOfName) {
    PtrList *fileNotes = createPtrList(0);

    FILE *notes = fopen(fileName, "r");
    if (notes == NULL) {
        puts("File reading error.");
        return fileNotes;
    }

    size_t readingBufferSize = 512;
    char *readingBuffer = NULL;

    char name[128];
    long phoneNumber;
    while (getline(&readingBuffer, &readingBufferSize, notes) != -1) {
        if (sscanf(readingBuffer, "%127s %ld", name, &phoneNumber) == 2) {
            appendPtr(fileNotes, makeNote(name, phoneNumber));
            *maxLengthOfName = *maxLengthOfName >= (int)strlen(name) ? *maxLengthOfName : (int)strlen(name);
        } else {
            printf("===Error parsing line: %s\n", readingBuffer);
        }
    }
    
    free(readingBuffer);
    fclose(notes);
    return fileNotes;
}

void displayNotes(PtrList *notes, int maxLengthOfName) {
    int nameWidth = maxLengthOfName;
    int phoneNumberWidth = 15;
    for (int i = 0; i < ptrListLength(notes); ++i) {
        Note *currentNote = peekPtr(notes, i);
        printf("- %-*s  %-*ld\n", nameWidth, currentNote->name, phoneNumberWidth, currentNote->phoneNumber);
    }
}

int lexicographicCompare(char *firstString, char *secondString) {
    while (*firstString && *secondString) {
        char charFromFirst = tolower((char)*firstString);
        char charFromSecond = tolower((char)*secondString);

        if (charFromFirst < charFromSecond) {
            return -1;
        } else if (charFromFirst > charFromSecond) {
            return 1;
        }

        ++firstString;
        ++secondString;
    }

    if (*firstString) {
        return 1;
    } else if (*secondString) {
        return -1;
    }
    return 0;
}

int compareNotesByName(void *first, void *second) {
    Note *firstNote = (Note *)first;
    Note *secondNote = (Note *)second;
    return lexicographicCompare(firstNote->name, secondNote->name);
}

int compareNotesByPhoneNumber(void *first, void *second) {
    Note *firstNote = (Note *)first;
    Note *secondNote = (Note *)second;
    return (firstNote->phoneNumber > secondNote->phoneNumber) - (firstNote->phoneNumber < secondNote->phoneNumber);
}