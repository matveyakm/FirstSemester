#include <stdio.h>
#include <stdbool.h>
#include "fileManager.h"

void startProcessing() { // идея глубины??
    int countOfNotesOnDisk;
    Note *notesOnDisk = loadFromFile(&countOfNotesOnDisk);
    int countOfTempNotes = 0;
    Note *tempNotes = malloc((100 - countOfNotesOnDisk) * sizeof(Note));

    int depth = 1;
    while (depth > 0) {
        int action;
        scanf("%d", &action);
        switch (action) {
        case 0:
            --depth;
            break;
        case 1:
            puts("Enter a name and a phone number to save it to temporary memory:");
            saveNote(tempNotes, countOfTempNotes);
            break;
        case 2:
            displayNotes(notesOnDisk, tempNotes, countOfNotesOnDisk, countOfTempNotes);
            break;
        case 3:
            puts("Enter a name to find phone number: ");
            findPhoneNumber(notesOnDisk, tempNotes, countOfNotesOnDisk, countOfTempNotes);
            break;
        case 4:
            puts("Enter a phone number to find its owner name: ");
            findName(notesOnDisk, tempNotes, countOfNotesOnDisk, countOfTempNotes);
            break;
        case 5:
            puts("Saving all notes to disk...");
            saveToDisk(notesOnDisk, tempNotes, countOfNotesOnDisk, countOfTempNotes);
            break;
        case 6:
            puts("\
            0 - exit\n\
            1 - add new note to temporary memory\n\
            2 - display notes\n\
            3 - find phone number by name\n\
            4 - find name by phone number\n\
            5 - save notes from temporary memory to disk\n\
            Enter one of this numbers to interact");
            break;
        default:
            puts("%d is not an availabel action. Enter '6' to help");
        }
    }
}