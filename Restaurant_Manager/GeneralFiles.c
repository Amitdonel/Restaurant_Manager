#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralFiles.h"


//**************** Text ********************
int readItemCountFromTxtFile(FILE* file, int* count) {
	if (fscanf(file, "%d\n", count) != 1) {
		return 0;
	}
	return 1;
}

//**************** Binary ******************
int readItemCountFromBinFile(FILE* file, int* count) {
	if (fread(count, sizeof(int), 1, file) != 1) {
		return 0;
	}
	return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
	if (fread(pVal, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		fclose(fp);
		return 0;
	}
	return 1;
}

char* readStringFromFile(FILE* fp, const char* msg)
{
	char* str;
	int length;
	if (!readIntFromFile(&length, fp, msg))
		return NULL;
	str = (char*)malloc((length) * sizeof(char));
	if (!str)
	{
		puts(msg);
		fclose(fp);
		return NULL;
	}
	if (fread(str, sizeof(char), length, fp) != length)
	{
		puts(msg);
		fclose(fp);
		return NULL;
	}
	return str;
}


