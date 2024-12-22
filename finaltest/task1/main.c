#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TEST_FAILED 52

int convertBinaryToDecimal(const char *binary) {
    int decimalForm = 0;
    for (int i = 0; i < strlen(binary); ++i) {
        decimalForm <<= 1;
        decimalForm = decimalForm | (binary[i] == '1');
    }
    return decimalForm;
}

char *convertIntToString(int integer) {
    int maxCountOfCharsInInt = 8 * sizeof(int);
    char *string = malloc(maxCountOfCharsInInt * sizeof(char));
    sprintf(string, "%d", integer);
    return string;
}

char *convertDecimalToBinary(int decimal) {
    int maxCountOfCharsInInt = sizeof(int) * 8;
    char *binary = malloc((maxCountOfCharsInInt + 1) * sizeof(char));
    for (int i = 0; i < maxCountOfCharsInInt; ++i) {
        binary[maxCountOfCharsInInt - i - 1] = decimal & 1 ? '1' : '0';
        decimal >>= 1;
    }
    binary[maxCountOfCharsInInt] = '\0';
    return binary;
}

bool validationTest(int testsLeft) {
    bool isTestSuccessful = true;
    srand(clock());
    int testValue = rand() % 10000;
    char *binaryForm = convertDecimalToBinary(testValue);
    isTestSuccessful *= convertBinaryToDecimal(binaryForm) == testValue;
    if (testsLeft <= 1) {
        return isTestSuccessful;
    }
    return isTestSuccessful * validationTest(testsLeft - 1);
}

int main() {
    if (!validationTest(100)) {
        puts("Test failed.");
        return TEST_FAILED;
    } else {
        puts("Ready to process.");
    }

    char *decimal = convertIntToString(convertBinaryToDecimal("1010"));
    printf("R %s\n", decimal);
    free(decimal);
    printf("T %s\n", convertDecimalToBinary(10));
}