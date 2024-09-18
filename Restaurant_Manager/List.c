/**************/
/*   list.c   */
/**************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
	if (!pList) return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}

/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value, int(*compare)(const void*, const void*))
{
	NODE* tmp;

	if (!pNode)
		return NULL; // no place to insert

	tmp = (NODE*)malloc(sizeof(NODE));	// new node
	if (!tmp)
		return NULL; // memory allocation failed

	while (pNode->next != NULL && compare(pNode->next->key, Value) < 0)
		pNode = pNode->next; // find the place to insert

	tmp->key = Value;
	tmp->next = pNode->next;
	pNode->next = tmp;
	return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, void (*freeKey)(void*))
{
	NODE* tmp;

	if (!pNode || !(tmp = pNode->next)) return False;

	pNode->next = tmp->next;
	freeKey(tmp->key);
	free(tmp);
	return True;
}

////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
void* L_print(const LIST* pList, void(*print)(const void*))
{
	NODE* tmp;
	int	c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		print(tmp->key);
	printf("\n");
	return (void*)(intptr_t)c;
}

////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
void* L_free(LIST* pList, void (*freeKey)(void*))
{
	NODE* tmp;

	if (!pList) return False;

	for (tmp = &(pList->head); L_delete(tmp, freeKey); );
	return (void*)True;
}

////////////////////////////////////////////////
// Save (additional function)
// Aim:		save the list content to a TXT file
// Input:	pointer to the list structure
// Output:	a number of the saved elements
////////////////////////////////////////////////
void* L_save(const LIST* pList, FILE* file, void(*saveKey)(FILE*, const void*))
{
	NODE* tmp;
	int		c = 0;

	if (!pList) return 0;

	for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
		saveKey(file, tmp->key);
	return (void*)(intptr_t)c;
}