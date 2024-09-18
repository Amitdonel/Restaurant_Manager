#include <stdio.h>
#include <stdlib.h>
#include "Restaurant.h"
#include "Admin.h"
#include "OrderList.h"
#include "General.h"

#define FROM_TXT_FILE 1
#define FROM_BINARY_FILE 2

int		userMenu();
void	displayAdminMenu(Menu* pMenu, OrderList* pOrderList, Restaurant* pRestaurant);
void	displayUserMenu(Menu* pMenu, OrderList* pOrderList, Restaurant* pRestaurant);
int		initRestaurantChoice();
int		saveProjectToTxtFile(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList);
int		saveProjectToBinFile(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList);
int		freeProject(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList);
int		printAscii();

typedef enum
{
	eDisplayMenu, ePlaceOrder, eAddCustomer, eqSort, eSearchFoodItem, eAdminLogin, eExit, eNofMenuOptions
}eMenuOptions;

const char* strMenu[eNofMenuOptions] =
{ "Display Menu","Place Order", "Join our membership", "Sort Menu", "Search food Item", "Admin Login", "Exit Menu" };


int main()
{
	Restaurant restaurant;
	OrderList orderList;
	Menu restaurantMenu;
	switch (initRestaurantChoice())
	{
		//Initialize project from text file
	case FROM_TXT_FILE:
		if (!initRestaurantFromTxtFile(&restaurant, "restaurant.txt"))
			initRestaurant(&restaurant);
		if (!initMenuFromTxtFile(&restaurantMenu, "menu.txt"))
			initMenu(&restaurantMenu);
		if (!initOrderListFromTxtFile(&orderList, &restaurantMenu, &restaurant, "orders.txt"))
			initOrderList(&orderList);
		break;
		//Initialize project from binary file
	case FROM_BINARY_FILE:
		if (!initRestaurantFromBinFile(&restaurant, "restaurant.bin"))
			initRestaurant(&restaurant);
		if (!initMenuFromBinFile(&restaurantMenu, "menu.bin"))
			initMenu(&restaurantMenu);
		if (!initOrderListFromBinFile(&orderList, &restaurantMenu, &restaurant, "orders.bin"))
			initOrderList(&orderList);
		break;

	default:
		printf("Invalid input\n");
		break;
	}
	printAscii();
	displayUserMenu(&restaurantMenu, &orderList, &restaurant);
	saveProjectToTxtFile(&restaurant, &restaurantMenu, &orderList);
	saveProjectToBinFile(&restaurant, &restaurantMenu, &orderList);
	freeProject(&restaurant, &restaurantMenu, &orderList);
	return 0;
}

int saveProjectToTxtFile(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList)
{
	if (!saveRestaurantToTxtFile(pRestaurant, "restaurant.txt"))
		return 0;
	if (!saveMenuToTxtFile(pMenu, "menu.txt"))
		return 0;
	if (!saveOrderListToTxtFile(pOrderList, "orders.txt"))
		return 0;
	return 1;
}

int saveProjectToBinFile(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList)
{
	if (!saveRestaurantToBinFile(pRestaurant, "restaurant.bin"))
		return 0;
	if (!saveMenuToBinFile(pMenu, "menu.bin"))
		return 0;
	if (!saveOrderListToBinFile(pOrderList, "orders.bin"))
		return 0;
	return 1;
}

int freeProject(Restaurant* pRestaurant, Menu* pMenu, OrderList* pOrderList)
{
	freeRestaurant(pRestaurant);
	freeMenu(pMenu);
	freeOrderList(pOrderList);
	return 1;
}


int initRestaurantChoice()
{
	int choice;
	printf("Please choose how to initialize the project:\n");
	printf("1. From Text file\n");
	printf("2. From Binary file\n");
	if(!scanf("%d", &choice))
		printf("Invalid input\n");
	do {
		if (choice != FROM_TXT_FILE && choice != FROM_BINARY_FILE)
		{
			printf("Invalid input\n");
			printf("Please choose how to initialize the project:\n");
			printf("1. From Text file\n");
			printf("2. From Binary file\n");
			if(!scanf("%d", &choice))
				printf("Invalid input\n");
		}
	} while (choice != FROM_TXT_FILE && choice != FROM_BINARY_FILE);
		

	CLEAR_BUFFER;
	return choice;
}

void displayUserMenu(Menu* pMenu, OrderList* pOrderList, Restaurant* pRestaurant)
{
	int userOption;
	do {
		userOption = userMenu();
		switch (userOption) {
		case eDisplayMenu:
			printMenu(pMenu);
			break;
		case ePlaceOrder:
			placeOrder(pOrderList, pMenu, pRestaurant);
			break;
		case eAddCustomer:
			addCustomer(pRestaurant);
			break;
		case eqSort:
			sortMenu(pMenu);
			break;
		case eSearchFoodItem:
			searchFoodItem(pMenu);
			break;
		case eAdminLogin:
			displayAdminMenu(pMenu, pOrderList, pRestaurant);
			break;
		case eExit:
			printf("Thank you for using the restaurant system. Hope to see you soon, Goodbye :)!\n");
			break;
		default:
			printf("Invalid option selected. Please try again.\n");
			break;
		}
	} while (userOption != eExit);
}

int userMenu()
{
	int userOption;
	printf("\nPlease choose from the following options:\n");
	for (int i = 0; i < eNofMenuOptions; i++)
	{
		printf("%d. %s\n", i, strMenu[i]);
	}
	if (!scanf("%d", &userOption))
		printf("Invalid input\n");

	CLEAR_BUFFER;
	return userOption;
}

void displayAdminMenu(Menu* pMenu, OrderList* pOrderList, Restaurant* pRestaurant)
{
	int adminOption;
	if (adminLogin(&pRestaurant->admin))
	{
		printf("\nWelcome back, admin");
		do
		{
			adminOption = adminMenu();
			switch (adminOption)
			{
			case eAddFoodItem:
				addItemToMenu(pMenu);
				break;
			case eRemoveFoodItem:
				removeItemFromMenu(pMenu);
				break;
			case eEditFoodItem:
				editItemFromMenu(pMenu);
				break;
			case eDisplayOrders:
				printOrderList(pOrderList);
				break;
			case eProcessFirstOrder:
				processOrder(pOrderList);
				break;
			case eDisplayAllCustomers:
				displayAllCustomers(pRestaurant);
				break;
			case eAdminExit:
				break;
			default:
				printf("Invalid option\n");
				break;
			}
		} while (adminOption != eAdminExit);

	}
}

int printAscii()
{
	printf("\n\n(___)---------------------------------------------------------(___)\n");
	printf("|   |                                                         |   |\n");
	printf("|   |  ____           _                              _        |   |\n");
	printf("|   | |  _ \\ ___  ___| |_ __ _ _   _ _ __ __ _ _ __ | |_      |   |\n");
	printf("|   | | |_) / _ \\ / __| __ / _` | | | | '__/ _` | '_ \\| __    |   |\n");
	printf("|   | |  _ < __ / \\__ \\ || (_| | |_| | | | (_| | | | | |_     |   |\n");
	printf("|   | |_| \\_\\___/\\___||___/ \\__\\__,_|\\__, |_| |_|\\__,_ |      |   |\n");
	printf("|   | |  \\/  | __ _ _ __   __ _  __ _  ___ _ __               |   |\n");
	printf("|   | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|              |   |\n");
	printf("|   | | |  | | (_| | | | | (_| | (_| |  __/ |                 |   |\n");
	printf("|   | |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|                 |   |\n");
	printf("|   |                              |___/                      |   |\n");
	printf("(___)---------------------------------------------------------(___)\n");

	return 1;
}