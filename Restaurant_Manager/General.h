#pragma once

#define MAX_STR_LEN 255
//MACROS
#define CLEAR_BUFFER while (getchar() != '\n')
#define CHECK_FILE_INIT(file) if (!file) { printf("Error opening file\n"); return 0; }
#define CHECK_FILE_SAVE(file) if (!file) { printf("Error saving file\n"); return 0; }
#define SUB(a,b) ((a) - (b))

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
int		getInt(const char* msg);
void	generalArrayFunction(void* arr, int size, int typeSize, void(*f)(void* element, int index));

