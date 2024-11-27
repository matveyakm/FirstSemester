#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[128];
    long phoneNumber;
} Note;

Note makeNote(char name[], long phoneNumber);
Note *loadFromFile(char *fileName, int *countOfNotes, bool *loadedSuccessfully);
bool addNote(Note *notes, int countOfNotes);
void displayNotes(Note *notes, int countOfFileNotes, int countOfTempNotes);
long findPhoneNumber(Note *notes, int countOfNotes, char *name);
char *findName(Note *notes, int countOfNotes, long phoneNumber);
bool saveToDisk(char *fileName, Note *notes, int countOfNotes);