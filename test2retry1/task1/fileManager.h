#pragma once
#include <stdbool.h>
#define INPUTFILE_NOT_FOUND -134
#define OUTPUTFILE_NOT_FOUND -132
#define VALUES_IS_NOT_CORRECT -122
#define OK 0

int processFile(const char *inputFile, const char *outputFile, int a, int b);