#pragma once
#include "def.h"

/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;

/*** Function prototypes ***/

BOOL	L_init(LIST* pList);

NODE* L_insert(NODE* pNode, DATA Value, int(*compare)(const void*, const void*));// insert new node after *pNode

BOOL	L_delete(NODE* pNode, void (*freeKey)(void*));// erase node after *pNode

void* L_print(const LIST* pList, void(*printer)(const void*));// print the list content

void* L_free(LIST* pList, void (*freeKey)(void*));// free list memory

void* L_save(const LIST* pList, FILE* file, void(*saveKey)(FILE*, const void*));// save list to TXT file

