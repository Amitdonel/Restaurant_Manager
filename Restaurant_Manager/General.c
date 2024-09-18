#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

int getInt(const char* msg)
{
	char strNum[MAX_STR_LEN];
	int num;
	int ok = 0;
	do
	{
		printf("%s\t", msg);
		if (myGets(strNum, MAX_STR_LEN))
		{
			ok = sscanf(strNum, "%d", &num);
			if (!ok)
				printf("Invalid integer number. Please try again.\n");
		}
	} while (!ok);
	return num;
}

void generalArrayFunction(void* arr, int size, int typeSize, void(*f)(void* element, int index))
{
	for (int i = 0; i < size; i++)
	{
		f((char*)arr + i * typeSize, i);
	}
}