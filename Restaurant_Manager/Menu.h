#pragma once
#include "FoodItem.h"
#include "General.h"
#include "GeneralFiles.h"

typedef enum { eSortByName, eSortByQuantity, eSortByPrice, eSortByCategory, eNotSorted, eNofSortOptions } eSortType;
static const char* sortTitles[eNofSortOptions] = { "Name", "Quantity", "Price", "Category" };

typedef struct {
	int numOfItems;
	foodItem** foodItemsArr;
	eSortType type;
}Menu;

int			initMenu(Menu* pMenu);
void		printMenu(const Menu* pMenu);
void		freeMenu(Menu* pMenu);

int			addItemToMenu(Menu* pMenu);
int			isItemAlreadyExists(Menu* pMenu, foodItem* pFoodItem);
foodItem* createFoodItem();
int			addFoodItemToMenuArr(Menu* pMenu, foodItem* pFoodItem);
int			getFoodItemIndex(const Menu* pMenu, const char* itemName);

int			getUserChoice(Menu* pMenu);
void		removeItemFromArray(Menu* pMenu, int index);
int			updateMenu(Menu* pMenu);
int			removeItemFromMenu(Menu* pMenu);
int			editItemFromMenu(Menu* pMenu);

void		sortMenu(Menu* pMenu);
eSortType	showSortMenu();
void		searchFoodItem(const Menu* pMenu);

int			compareMenuItemByName(const void* meal1, const void* meal2);
int			compareMenuItemByQuantity(const void* meal1, const void* meal2);
int			compareMenuItemByPrice(const void* meal1, const void* meal2);
int			compareMenuItemByCategory(const void* meal1, const void* meal2);

int			allocateMemoryForFoodItems(Menu* pMenu, int count);

int			saveMenuToTxtFile(const Menu* pMenu, const char* fileName);
int			initMenuFromTxtFile(Menu* pMenu, const char* fileName);
int			readFoodItemsFromTxtFile(Menu* pMenu, FILE* file);

int			saveMenuToBinFile(const Menu* pMenu, const char* fileName);
int			initMenuFromBinFile(Menu* pMenu, const char* fileName);
int			readFoodItemsFromBinFile(Menu* pMenu, FILE* file);
