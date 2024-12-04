#include <stdio.h>
#include <string.h>
#include "../../localLibs/trees/binTree.h"

int cmp(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

char *donothing(void *a) {
    return (char *)a;
}

char *makeStr(char charsOnStack[]) {
    char *string = malloc(strlen(charsOnStack) *sizeof(char));
    strcpy(string, charsOnStack);
    return string;
}

int main() {
    /*
    binTreeNode *root = createNode("Hermi");
    addToBST(root, makeStr("Boris"), cmp);
    addToBST(root, makeStr("Ceil"), cmp);
    addToBST(root, makeStr("Arc"), cmp);
    addToBST(root, makeStr("Zen"), cmp);
    addToBST(root, makeStr("Abc"), cmp);
    addToBST(root, makeStr("Gum"), cmp);
    addToBST(root, makeStr("Fermi"), cmp);
    addToBST(root, makeStr("Key"), cmp);
    addToBST(root, makeStr("lada2"), cmp);
    addToBST(root, makeStr("lada1"), cmp);
    addToBST(root, makeStr("lada3"), cmp);

    printNode(root, donothing);
    printf("%d\n", freeFromBST(root, "Boris", cmp));
    addToBST(root, makeStr("Boris"), cmp);
    // binTreeNode *lada3 = findInBST(root, "lada3", cmp);
    // printf("30ML %s\n", getNodeData(lada3));
    // addLeftChild(lada3, createNode("matvey"));
    puts("\n\n");

    printNode(root, donothing);
    */
}