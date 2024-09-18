#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "foodItem.h"


int initFoodItem(foodItem* pFoodItem)
{
	if (!pFoodItem)
		return 0;

	pFoodItem->name = getStrExactName("Enter food item name: ");
	pFoodItem->price = getInt("Enter food item price: ");
	pFoodItem->quantity = getInt("Enter food item quantity: ");
	pFoodItem->type = getFoodItemType();
	return 1;
}

mealType getFoodItemType()
{
	int i;
	for (i = 0; i < eNofMealTypes; i++)
	{
		printf("%d. %s\n", i + 1, mealTypeStrings[i]);
	}
	printf("Please enter food item type: ");
	int option;
	if (!scanf("%d", &option))
		return -1;
	while (option < 1 || option > eNofMealTypes)
	{
		printf("Invalid option. Please try again: ");
		if (!scanf("%d", &option))
			return -1;
	}
	return option - 1;
}

int isSameFoodItem(const foodItem* pFoodItem1, const foodItem* pFoodItem2)
{
	if (!pFoodItem1 || !pFoodItem2)
		return 0;

	if (strcmp(pFoodItem1->name, pFoodItem2->name) == 0)
		return 1;

	return 0;
}

void printFoodItem(const foodItem* pFoodItem, int index)
{
	if (!pFoodItem)
		return;

	printf("| %-8d | %-20s | %-9d | %-9d | %-11s |\n", index + 1, pFoodItem->name, pFoodItem->price, pFoodItem->quantity, mealTypeStrings[pFoodItem->type]);
}

void printFoodItemVoid(const void* pFoodItem, int index)
{
	const foodItem* pFood = *(const foodItem**)pFoodItem;
	printFoodItem(pFood, index);
}

void freeFoodItem(foodItem* pFoodItem)
{
	if (!pFoodItem)
		return;
	free(pFoodItem->name);
	free(pFoodItem);
}

void freeFoodItemVoid(void* pFoodItem, int index)
{
	freeFoodItem(*(foodItem**)pFoodItem);
}

//******************************************* text file *****************************************************
int saveFoodItemToTxtFile(const foodItem* pFoodItem, FILE* fileName)
{
	if (!pFoodItem || !fileName)
		return 0;
	fprintf(fileName, "%s\n%d\n%d\n%d\n", pFoodItem->name, pFoodItem->price, pFoodItem->quantity, pFoodItem->type);
	return 1;
}

int readFoodItemFromTxtFile(foodItem* pFoodItem, FILE* fileName)
{
	if (!pFoodItem || !fileName)
		return 0;
	char temp[MAX_STR_LEN];
	if (!fgets(temp, MAX_STR_LEN, fileName))
		return 0;
	temp[strcspn(temp, "\n")] = 0;
	pFoodItem->name = getDynStr(temp);
	if (!pFoodItem->name)
		return 0;
	if (!fscanf(fileName, "%d\n%d\n%d\n", &pFoodItem->price, &pFoodItem->quantity, &pFoodItem->type))
		return 0;
	return 1;
}
//************************************ binary compressed file ***********************************************
int	saveFoodItemToBinFileCompressed(const foodItem* pFoodItem, FILE* fileName)
{
	BYTE data[3] = { 0 };

	int len = (int)strlen(pFoodItem->name);
	data[0] = len << 3;
	data[0] |= pFoodItem->type << 1;
	data[0] |= (pFoodItem->quantity >> 7) & 0x01; // Only take the highest bit
	data[1] = (pFoodItem->quantity << 1) & 0xFF; // Make sure we don't go beyond 8 bits
	data[1] |= (pFoodItem->price >> 8) & 0xFF; // Take only 8 bits from price
	data[2] = pFoodItem->price & 0xFF; // Take only lowest 8 bits from price

	if (fwrite(data, sizeof(BYTE), 3, fileName) != 3)
		return 0;

	if (fwrite(pFoodItem->name, sizeof(char), len, fileName) != len)
		return 0;

	return 1;
}

int readFoodItemFromBinFileCompressed(foodItem* pFoodItem, FILE* fileName)
{
	BYTE data[3];
	if (fread(data, sizeof(BYTE), 3, fileName) != 3)
		return 0;

	pFoodItem->name = (char*)malloc((data[0] >> 3) + 1); // Allocate memory for name
	if (!pFoodItem->name)
		return 0;
	fread(pFoodItem->name, sizeof(char), (data[0] >> 3), fileName);
	pFoodItem->name[data[0] >> 3] = '\0'; // Null-terminate the string

	pFoodItem->type = (data[0] >> 1) & 0x03; // Mask out only 2 bits
	pFoodItem->quantity = ((data[0] & 0x01) << 7) | (data[1] >> 1); // Combine the first bit from data[0] with the rest from data[1]
	pFoodItem->price = ((data[1] & 0x01) << 8) | data[2]; // Combine the first bit from data[1] with data[2]

	return 1;
}