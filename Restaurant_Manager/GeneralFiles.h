#pragma once

int		readItemCountFromTxtFile(FILE* file, int* count);

int		readItemCountFromBinFile(FILE* file, int* count);
char* readStringFromFile(FILE* fp, const char* msg);
int		readIntFromFile(int* pVal, FILE* fp, const char* msg);

