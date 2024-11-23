#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "noteManager.h"
#include "../../localLibs/list/pointerList.h"
#include "../../localLibs/mergeSort/mergeSort.h"

void startProcessing(char *fileName) {
    int maxLengthOfName = 0;
    PtrList *notes = loadFromFile(fileName, &maxLengthOfName);
    if (notes == NULL) {
        puts("File reading failed.");
        return;
    }
    PtrList *notesSortedByName = representPtrList(notes);
    PtrList *notesSortedByPhone = representPtrList(notes);
    bool needToLoop = true;
    while (needToLoop) {
        int action;
        puts("==Enter a command:");
        if (scanf("%d", &action) != 1) {
            puts("===You can only enter a integer number!===\nExiting...\n");
            break;
        }

        switch (action) {
        case 0:
            needToLoop = false;
            break;

        case 1:
            displayNotes(notes, maxLengthOfName);
            break;

        case 2:
            mergeSort(notesSortedByName, compareNotesByName);
            displayNotes(notesSortedByName, maxLengthOfName);
            break;

        case 3:
            mergeSort(notesSortedByPhone, compareNotesByPhoneNumber);
            displayNotes(notesSortedByPhone, maxLengthOfName);
            break;

        default:
            puts("\
            0 - exit\n\
            1 - display notes in the origin order\n\
            2 - display notes sorted by name\n\
            3 - display notes sorted by phone number\n\
            4 - help\n\
            Enter one of this numbers to interact");
            break;
        }
    }
    free(notesSortedByName);
    free(notesSortedByPhone);
    deletePtrList(notes);
}