#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "noteManager.h"
#include "../../localLibs/list/pointerList.h"
#include "../../localLibs/mergeSort/mergeSort.h"
#include "../../localLibs/testingTools/testingTools.h"

void fillTestFile(char *fileName) {
    FILE *file = fopen(fileName, "w");
    int linesLeft = 12345;

    char *randomString = malloc(111 * sizeof(char));
    while (linesLeft > 0) {
        srand(clock() - linesLeft);
        int lengthOfName = rand() % 109 + 1;
        for (int i = 0; i < lengthOfName; ++i) {
            randomString[i] = (char)(rand() % 25 + 65);
        }
        randomString[lengthOfName] = '\0';
        fprintf(file, "%s %d\n", randomString, rand() % 1000000);
        --linesLeft;
    }
    fclose(file);
    free(randomString);
}

bool isPtrListSorted(PtrList *list, int (*compare)(void *, void*)) {
    for (int i = 1; i < ptrListLength(list); ++i) {
        if (compare(peekPtr(list, i - 1), peekPtr(list, i)) > 0) {
            return false;
        }
    }
    return true;
}

bool validationTest(int countOfTests) {
    bool isTestSuccesful = true;
    char fileName[] = "mergeSortTestFile.txt";
    fillTestFile(fileName);
    int useless = 0;
    PtrList *notes = loadFromFile(fileName, &useless);

    mergeSort(notes, compareNotesByName);
    isTestSuccesful *= isPtrListSorted(notes, compareNotesByName);

    mergeSort(notes, compareNotesByPhoneNumber);
    isTestSuccesful *= isPtrListSorted(notes, compareNotesByPhoneNumber);

    if (countOfTests == 1) {
        return isTestSuccesful;
    }
    deletePtrList(notes);
    return isTestSuccesful * validationTest(countOfTests - 1);
}