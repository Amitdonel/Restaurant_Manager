#pragma once 
#include "General.h"
#include "GeneralFiles.h"

typedef unsigned char BYTE;

typedef enum { eAppetizers, eMainCourse, eBeverage, eNofMealTypes } mealType;
static const char* mealTypeStrings[eNofMealTypes] = { "Appetizers", "Main Course", "Beverage" };

typedef struct
{
	char* name;
	int price;
	int quantity;
	mealType type;
} foodItem;

int  		initFoodItem(foodItem* pFoodItem);
int			isSameFoodItem(const foodItem* pFoodItem1, const foodItem* pFoodItem2);
void		printFoodItem(const foodItem* pFoodItem, int index);
void		printFoodItemVoid(const void* pFoodItem, int index);
void		freeFoodItem(foodItem* pFoodItem);
void		freeFoodItemVoid(void* pFoodItem, int index);
mealType	getFoodItemType();

int			readFoodItemFromTxtFile(foodItem* pFoodItem, FILE* fileName);
int			saveFoodItemToTxtFile(const foodItem* pFoodItem, FILE* fileName);

int			saveFoodItemToBinFileCompressed(const foodItem* pFoodItem, FILE* fileName);
int			readFoodItemFromBinFileCompressed(foodItem* pFoodItem, FILE* fileName);