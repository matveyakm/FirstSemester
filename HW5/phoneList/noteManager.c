#include <stdio.h>
#include <stdlib.h>
#include "fileManager.h"

Note makeNote(char *name, long phoneNumber) {
    Note res = {.name = name, .phoneNumber = phoneNumber};
    return res;
}

Note *loadFromFile(char *fileName, int *countOfNotes) {
    FILE *notes = fopen(fileName, "r");
    if (notes == NULL) {
        puts("File reading error.");
        exit(1);
    }
    
    *countOfNotes = 0;
    Note *fileNotes = malloc(100 * sizeof(Note));

    size_t readingBufferSize = 256;
    char *readingBuffer = malloc(readingBufferSize * sizeof(char));

    char *name;
    long phoneNumber;
    while (getline(&readingBuffer, &readingBufferSize, fileNotes) != -1) {
        if (sscanf(readingBuffer, "%s %ld", &name, &phoneNumber) == 2) {
            fileNotes[*countOfNotes] = makeNote(name, phoneNumber);
            ++countOfNotes;
        } else {
            printf("Error parsing line: %s\n", readingBuffer);
        }
    }

    fclose(notes);
    return fileNotes;
}

void addNote(Note *notes, int *countOfNotes) {
    char *name;
    long phoneNumber;
    puts("Enter new note:");
    scanf("%s %ld", &name, &phoneNumber);
    notes[(int)countOfNotes] = makeNote(name, phoneNumber); // ???????
    ++countOfNotes;
}

void displayNotes(Note *fileNotes, Note *tempNotes, int countOfFileNotes, int countOfTempNotes) {
    puts("Notes loaded from file:");
    for (int i = 0; i < countOfFileNotes; ++i) {
        printf("%s %ld", fileNotes[i].name, fileNotes[i].phoneNumber);
    }
    puts("Notes saved to temporary memory:");
    for (int i = 0; i < countOfTempNotes; ++i) {
        printf("%s %ld", tempNotes[i].name, tempNotes[i].phoneNumber);
    }
}