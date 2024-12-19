#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noteManager.h"
#include "inputHandler.h"
#include "../../localLibs/arrayFuncs/arrayFuncs.h"

Note makeNote(char name[], long phoneNumber) {
    Note res;
    strncpy(res.name, name, sizeof(res.name) - 1);
    res.phoneNumber = phoneNumber;
    return res;
}

Note *loadFromFile(char *fileName, int *countOfNotes, bool *loadedSuccessfully) {
    *countOfNotes = 0;
    Note *fileNotes = malloc(MAX_COUNT_OF_NOTES * sizeof(Note));

    FILE *notes = fopen(fileName, "r");
    if (notes == NULL) {
        *loadedSuccessfully = false;
        return fileNotes;
    }

    size_t readingBufferSize = 256;
    char *readingBuffer = NULL;

    char name[128] = "";
    long phoneNumber = 0;
    while (getline(&readingBuffer, &readingBufferSize, notes) != -1) {
        if (sscanf(readingBuffer, "%127s %ld", name, &phoneNumber) == 2) {
            fileNotes[*countOfNotes] = makeNote(name, phoneNumber);
            ++(*countOfNotes);
        } else {
            printf("===Error parsing line: %s\n", readingBuffer);
        }
    }
    
    free(readingBuffer);
    fclose(notes);
    *loadedSuccessfully = true;
    return fileNotes;
}

bool addNote(Note *notes, int countOfNotes) {
    char name[128];
    long phoneNumber;
    if (scanf("%127s %ld", name, &phoneNumber) != 2) {
        return false;
    }
    notes[countOfNotes] = makeNote(name, phoneNumber);
    return true;
}

void displayNotes(Note *notes, int countOfFileNotes, int countOfTempNotes) {
    puts(countOfFileNotes ? "=Notes loaded from file:" : "=No notes loaded from file.");
    for (int i = 0; i < countOfFileNotes; ++i) {
        printf("-%s %ld\n", notes[i].name, notes[i].phoneNumber);
    }
    puts(countOfTempNotes ? "=Notes saved to temporary memory:" : "=No notes in temporary memory.");
    for (int i = countOfFileNotes; i < countOfTempNotes + countOfFileNotes; ++i) {
        printf("-%s %ld\n", notes[i].name, notes[i].phoneNumber);
    }
}

long findPhoneNumber(Note *notes, int countOfNotes, char *name) {
    for (int i = 0; i < countOfNotes; ++i) {
        if (strcmp(notes[i].name, name) == 0) {
            return notes[i].phoneNumber;
        }
    }
    return -1;
}

char *findName(Note *notes, int countOfNotes, long phoneNumber) {
    for (int i = 0; i < countOfNotes; ++i) {
        if (phoneNumber == notes[i].phoneNumber) {
            return notes[i].name; 
        }
    }
    return "";
}

bool saveToDisk(char *fileName, Note *notes, int countOfNotes) {
    FILE *file = fopen(fileName, "w");
    bool isSavingSuccesful = file != NULL;
    for (int i = 0; i < countOfNotes; ++i) {
        isSavingSuccesful *= fprintf(file, "%s %ld\n", notes[i].name, notes[i].phoneNumber) >= 0;
    }
    isSavingSuccesful *= fclose(file) == 0;
    return isSavingSuccesful;
}