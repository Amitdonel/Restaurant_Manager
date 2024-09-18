#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Menu.h"

int initMenu(Menu* pMenu)
{
	pMenu->numOfItems = 0;
	pMenu->foodItemsArr = NULL;
	pMenu->type = eNotSorted;
	return 1;
}

int addItemToMenu(Menu* pMenu) {
	foodItem* pFoodItem = createFoodItem();
	if (!pFoodItem)
		return 0;

	if (isItemAlreadyExists(pMenu, pFoodItem)) {
		printf("Item \"%s\" already exists in the menu.\n", pFoodItem->name);
		freeFoodItem(pFoodItem);
		return 0;
	}

	if (!addFoodItemToMenuArr(pMenu, pFoodItem)) {
		freeFoodItem(pFoodItem);
		return 0;
	}

	printMenu(pMenu);
	printf("\nItem \"%s\" added to the menu.\n", pFoodItem->name);
	return 1;
}

int isItemAlreadyExists(Menu* pMenu, foodItem* pFoodItem) {
	for (int i = 0; i < pMenu->numOfItems; i++) {
		if (isSameFoodItem(pMenu->foodItemsArr[i], pFoodItem)) {
			return 1;
		}
	}
	return 0;
}

foodItem* createFoodItem() {
	foodItem* pFoodItem = (foodItem*)calloc(1, sizeof(foodItem));
	if (!pFoodItem)
		return NULL;

	if (!initFoodItem(pFoodItem)) {
		free(pFoodItem);
		return NULL;
	}

	return pFoodItem;
}

int addFoodItemToMenuArr(Menu* pMenu, foodItem* pFoodItem) {
	foodItem** temp = (foodItem**)realloc(pMenu->foodItemsArr, (pMenu->numOfItems + 1) * sizeof(foodItem*));
	if (!temp)
		return 0;

	pMenu->foodItemsArr = temp;
	pMenu->foodItemsArr[pMenu->numOfItems] = pFoodItem;
	pMenu->numOfItems++;
	return 1;
}

int removeItemFromMenu(Menu* pMenu) {
	printMenu(pMenu);
	int userChoice = getUserChoice(pMenu);
	if (!userChoice)
		return 0;

	foodItem* itemToRemove = pMenu->foodItemsArr[userChoice - 1];
	if (!itemToRemove) {
		printf("Item did not found in the menu.\n");
		return 0;
	}
	removeItemFromArray(pMenu, userChoice);
	printf("Item \"%s\" removed from the menu.\n", itemToRemove->name);
	freeFoodItem(itemToRemove);

	if (!updateMenu(pMenu))
		return 0;
	return 1;
}

void removeItemFromArray(Menu* pMenu, int index) {
	for (int i = index - 1; i < pMenu->numOfItems - 1; i++)
		pMenu->foodItemsArr[i] = pMenu->foodItemsArr[i + 1];
	pMenu->numOfItems--;
}

int updateMenu(Menu* pMenu) {
	foodItem** temp = (foodItem**)realloc(pMenu->foodItemsArr, pMenu->numOfItems * sizeof(foodItem*));
	if (!temp)
		return 0;
	pMenu->foodItemsArr = temp;
	return 1;
}

int editItemFromMenu(Menu* pMenu)
{
	printMenu(pMenu);
	int userChoice = getUserChoice(pMenu);
	if (!userChoice)
		return 0;

	foodItem* itemToEdit = pMenu->foodItemsArr[userChoice - 1];

	if (itemToEdit != NULL)
	{
		freeFoodItem(itemToEdit);
		foodItem* pFoodItem = (foodItem*)calloc(1, sizeof(foodItem));
		if (!pFoodItem)
			return 0;
		printf("*New item details*\n");
		initFoodItem(pFoodItem);
		// Update the found item in the menu with the new details
		*itemToEdit = *pFoodItem;
		free(pFoodItem);
		printf("Item \"%s\" edited in the menu.\n", itemToEdit->name);
	}
	else
		printf("Item did not found in the menu.\n");

	return 1;
}

int getUserChoice(Menu* pMenu) {
	int userChoice = getInt("Enter the number of the food item you would like to choose: ");
	if (userChoice < 1 || userChoice > pMenu->numOfItems) {
		printf("Invalid item number. try again..\n");
		return 0;
	}
	return userChoice;
}

eSortType showSortMenu()
{
	int option;
	printf("Please choose a sorting option:\n");
	do {
		for (int i = 0; i < eNofSortOptions - 1; i++)
			printf("%d. %s\n", i, sortTitles[i]);
		if (!scanf("%d", &option))
			printf("Invalid input\n");
	} while (option < 0 || option > eNofSortOptions);
	return (eSortType)option;
}

void sortMenu(Menu* pMenu)
{
	pMenu->type = showSortMenu();
	int(*compare)(const void*, const void*) = NULL;

	switch (pMenu->type)
	{
	case eSortByName:
		compare = compareMenuItemByName;
		break;
	case eSortByQuantity:
		compare = compareMenuItemByQuantity;
		break;
	case eSortByPrice:
		compare = compareMenuItemByPrice;
		break;
	case eSortByCategory:
		compare = compareMenuItemByCategory;
		break;
	}
	if (compare)
		qsort(pMenu->foodItemsArr, pMenu->numOfItems, sizeof(foodItem*), compare);
	printMenu(pMenu);
}

void searchFoodItem(const Menu* pMenu)
{
	int(*compare)(const void*, const void*) = NULL;
	foodItem meal = { 0 };
	foodItem* pFoodItem = &meal;

	switch (pMenu->type)
	{
	case eSortByName:
		meal.name = getStrExactName("Enter Food Item Name:");
		compare = compareMenuItemByName;
		break;
	case eSortByQuantity:
		meal.quantity = getInt("Enter Food Item Quantity:");
		compare = compareMenuItemByQuantity;
		break;
	case eSortByPrice:
		meal.price = getInt("Enter Food Item Price:");
		compare = compareMenuItemByPrice;
		break;
	case eSortByCategory:
		meal.type = getFoodItemType();
		compare = compareMenuItemByCategory;
		break;
	}
	if (compare)
	{
		foodItem** pFound = (foodItem**)bsearch(&pFoodItem, pMenu->foodItemsArr, pMenu->numOfItems, sizeof(foodItem*), compare);
		if (pFound)
			printFoodItem(*pFound, getFoodItemIndex(pMenu, (*pFound)->name));
		else
			printf("Food item not found\n");
	}
	else {
		printf("Search cannot be performed, Menu is not sorted..\n");
	}
}

int getFoodItemIndex(const Menu* pMenu, const char* itemName)
{
	for (int i = 0; i < pMenu->numOfItems; i++)
	{
		if (strcmp(pMenu->foodItemsArr[i]->name, itemName) == 0)
			return i;
	}
	return -1;
}

int compareMenuItemByName(const void* meal1, const void* meal2)
{
	foodItem* pFoodItem1 = *(foodItem**)meal1;
	foodItem* pFoodItem2 = *(foodItem**)meal2;
	return strcmp(pFoodItem1->name, pFoodItem2->name);
}

int compareMenuItemByQuantity(const void* meal1, const void* meal2)
{
	foodItem* pFoodItem1 = *(foodItem**)meal1;
	foodItem* pFoodItem2 = *(foodItem**)meal2;
	return SUB(pFoodItem1->quantity, pFoodItem2->quantity);
}

int compareMenuItemByPrice(const void* meal1, const void* meal2)
{
	foodItem* pFoodItem1 = *(foodItem**)meal1;
	foodItem* pFoodItem2 = *(foodItem**)meal2;
	return SUB(pFoodItem1->price, pFoodItem2->price);
}

int compareMenuItemByCategory(const void* meal1, const void* meal2)
{
	foodItem* pFoodItem1 = *(foodItem**)meal1;
	foodItem* pFoodItem2 = *(foodItem**)meal2;
	return SUB(pFoodItem1->type, pFoodItem2->type);
}

void printMenu(const Menu* pMenu)
{
	if (!pMenu)
	{
		printf("Menu is empty\n");
		return;
	}
	printf("\n|----------|----------------------|-----------|-----------|-------------|\n");
	printf("| %-8s | %-20s | %-10s| %-10s| %-12s|\n", "No.", "Name", "Price ($)", "Quantity", "Category");
	printf("|----------|----------------------|-----------|-----------|-------------|\n");
	generalArrayFunction((void*)pMenu->foodItemsArr, pMenu->numOfItems, sizeof(foodItem*), printFoodItemVoid);

	printf("|----------|----------------------|-----------|-----------|-------------|\n");
}

void freeMenu(Menu* pMenu)
{
	if (!pMenu)
		return;

	generalArrayFunction((void*)pMenu->foodItemsArr, pMenu->numOfItems, sizeof(foodItem*), freeFoodItemVoid);
	free(pMenu->foodItemsArr);
	pMenu->numOfItems = 0;
	pMenu->type = eNotSorted;
}

// Function to allocate memory for the food items array
int allocateMemoryForFoodItems(Menu* pMenu, int count) {
	pMenu->numOfItems = count;
	pMenu->foodItemsArr = (foodItem**)malloc(count * sizeof(foodItem*));
	if (!pMenu->foodItemsArr) {
		printf("Memory allocation failed\n");
		return 0;
	}
	return 1;
}

//******************************************* text files *****************************************************

int initMenuFromTxtFile(Menu* pMenu, const char* fileName) {
	FILE* file = fopen(fileName, "r");
	CHECK_FILE_INIT(file);

	int count = 0;
	if (!readItemCountFromTxtFile(file, &count)) {
		fclose(file);
		return 0;
	}

	if (!allocateMemoryForFoodItems(pMenu, count)) {
		fclose(file);
		return 0;
	}

	if (!readFoodItemsFromTxtFile(pMenu, file)) {
		fclose(file);
		return 0;
	}
	fclose(file);
	return 1;
}

int readFoodItemsFromTxtFile(Menu* pMenu, FILE* file) {
	for (int i = 0; i < pMenu->numOfItems; i++) {
		foodItem* pFoodItem = (foodItem*)malloc(sizeof(foodItem));
		if (!pFoodItem) {
			return 0;
		}
		if (!readFoodItemFromTxtFile(pFoodItem, file)) {
			return 0;
		}
		pMenu->foodItemsArr[i] = pFoodItem;
	}
	return 1;
}

int saveMenuToTxtFile(const Menu* pMenu, const char* fileName)
{
	FILE* file = fopen(fileName, "w");
	CHECK_FILE_SAVE(file);
	int count = pMenu->numOfItems;
	fprintf(file, "%d\n", count);

	for (int i = 0; i < count; i++)
		saveFoodItemToTxtFile(pMenu->foodItemsArr[i], file);

	fclose(file);
	return 1;
}

//******************************************* binary files *****************************************************
int initMenuFromBinFile(Menu* pMenu, const char* fileName)
{
	FILE* file;
	file = fopen(fileName, "rb");
	CHECK_FILE_INIT(file);
	pMenu->foodItemsArr = NULL;
	fread(&pMenu->numOfItems, sizeof(int), 1, file);

	if (!allocateMemoryForFoodItems(pMenu, pMenu->numOfItems))
	{
		fclose(file);
		return 0;
	}

	if (!readFoodItemsFromBinFile(pMenu, file))
	{
		fclose(file);
		return 0;
	}
	return 1;
}

int readFoodItemsFromBinFile(Menu* pMenu, FILE* file)
{
	for (int i = 0; i < pMenu->numOfItems; i++)
	{
		foodItem* pFoodItem = (foodItem*)calloc(1, sizeof(foodItem));
		if (!pFoodItem)
			return 0;
		if (!readFoodItemFromBinFileCompressed(pFoodItem, file))
			return 0;
		pMenu->foodItemsArr[i] = pFoodItem;
	}
	return 1;
}

int saveMenuToBinFile(const Menu* pMenu, const char* fileName)
{
	FILE* file = fopen(fileName, "wb");
	if (!file)
	{
		printf("Error saving Menu\n");
		return 0;
	}
	int count = pMenu->numOfItems;
	fwrite(&count, sizeof(int), 1, file);
	for (int i = 0; i < count; i++)
		saveFoodItemToBinFileCompressed(pMenu->foodItemsArr[i], file);
	fclose(file);
	return 1;
}


