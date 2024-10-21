#pragma once
#include <stdlib.h>

typedef struct {
    char *name;
    long phoneNumber;
} Note;

Note *loadFromFile(char *fileName, int *countOfNotes);
Note makeNote(char *name, long phoneNumber);
void addNote(Note *notes, int *countOfNotes);