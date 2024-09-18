#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Order.h"


// Function to initialize the order
int initOrder(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant) {
	//init order customer
	Customer* pCustomer = initOrderCustomer(pRestaurant);
	pOrder->customer = pCustomer;
	//init order food item
	foodItem* foundItem = initOrderFoodItem(pMenu);
	if (foundItem == NULL)
		return 0;
	pOrder->item = foundItem;
	//init order quantity
	if (!initOrderQuantity(pOrder))
		return 0;
	//init order price
	if (!initOrderPrice(pOrder))
		return 0;
	//init order date
	Date* pDate = initOrderDate();
	if (pDate == NULL)
		return 0;
	pOrder->date = pDate;
	//init order ID
	if (!initOrderID(pOrder))
		return 0;
	return 1;
}

// Function to initialize the customer for the order
Customer* initOrderCustomer(Restaurant* pRestaurant) {
	int isMember = hasMemberShip();
	Customer* pCustomer = NULL; // Initialize to NULL initially
	if (isMember) {
		pCustomer = findACustomer(pRestaurant);
		if (!pCustomer) {
			printf("Unable to find existing customer.\n\n");
		}
		else {
			printf("\nWelcome back %s!\n", pCustomer->name);
		}
	}

	if (!pCustomer || !isMember) {
		pCustomer = (Customer*)malloc(sizeof(Customer));
		if (!pCustomer) {
			printf("Memory allocation failed.\n");
			return NULL; // Return NULL indicating failure
		}
		initCustomer(pCustomer);
	}
	return pCustomer;
}

// Function to initialize the food item for the order
foodItem* initOrderFoodItem(Menu* pMenu) {
	printMenu(pMenu);
	printf("\n");
	int userChoice = getInt("Enter the number of the food item you would like to order: ");
	do {
		if (userChoice < 1 || userChoice > pMenu->numOfItems) {
			printf("Invalid choice.\n");
			userChoice = getInt("Enter the number of the food item you would like to order: ");
		}
	} while (userChoice < 1 || userChoice > pMenu->numOfItems);

	foodItem* foundItem = pMenu->foodItemsArr[userChoice - 1];
	if (!foundItem) {
		printf("Unable to find the food item.\n");
		return NULL;
	}
	return foundItem;
}

// Function to initialize the quantity for the order
int initOrderQuantity(Order* pOrder) {
	do {
		pOrder->orderQuantity = getInt("Enter the quantity of the food item: ");
	} while (!(checkQuantity(pOrder)));

	pOrder->item->quantity = SUB(pOrder->item->quantity, pOrder->orderQuantity);
	return 1;
}

int checkQuantity(Order* pOrder)
{
	if ((pOrder->item->quantity - pOrder->orderQuantity) < 0)
	{
		printf("The quantity of '%s' is %d. Please try again..\n", pOrder->item->name, pOrder->item->quantity);
		return 0;
	}
	if (pOrder->orderQuantity <= 0)
	{
		printf("The quantity of the food item is invalid. Please try again..\n");
		return 0;
	}
	return 1;
}

// Function to initialize the price for the order
int initOrderPrice(Order* pOrder) {
	pOrder->orderPrice =
		pOrder->orderQuantity * pOrder->item->price;
	return 1;
}

// Function to initialize the date for the order
Date* initOrderDate() {
	Date* pDate = (Date*)malloc(sizeof(Date));
	if (!initDate(pDate))
		return NULL;
	return pDate;
}

// Function to initialize the ID for the order
int initOrderID(Order* pOrder) {
	time_t t;
	srand((unsigned)time(&t));
	pOrder->orderID = rand() % 500;
	return 1;
}

// Function to check if the customer is a member
int hasMemberShip() {
	printf("Are You a Member? (Y/N): ");
	while (1) {
		char c;
		if (!scanf(" %c", &c))
			printf("Invalid input.\nPlease enter Y or N: ");
		else if (c == 'Y' || c == 'y')
			return 1;
		else if (c == 'N' || c == 'n')
			return 0;
		else
			printf("Invalid input.\nPlease enter Y or N: ");

		while (getchar() != '\n');
	}
}

// Function to compare orders by date
int compareOrdersByDate(const void* order1, const void* order2)
{
	const Order* p1 = (const Order*)order1;
	const Order* p2 = (const Order*)order2;
	if (p1->date->year != p2->date->year)
		return SUB(p1->date->year, p2->date->year);
	if (p1->date->month != p2->date->month)
		return SUB(p1->date->month, p2->date->month);
	if (p1->date->day != p2->date->day)
		return SUB(p1->date->day, p2->date->day);
	if (p1->date->hour != p2->date->hour)
		return SUB(p1->date->hour, p2->date->hour);
	if (p1->date->minute != p2->date->minute)
		return SUB(p1->date->minute, p2->date->minute);
	if (p1->date->second != p2->date->second)
		return SUB(p1->date->second, p2->date->second);
	return 0;
}

void printOrder(const void* pOrder)
{
	const Order* p = (const Order*)pOrder;
	printf("\nOrder ID: %d\n", p->orderID);
	printf("Customer: %s\n", p->customer->name);
	printf("Food Item Name: %s\n", p->item->name);
	printf("Quantity: %d\n", p->orderQuantity);
	printf("Price($): %d\n", p->orderPrice);
	printf("Date: %02d/%02d/%02d  %02d:%02d:%02d\n",
		p->date->day, p->date->month, p->date->year, p->date->hour, p->date->minute, p->date->second);
	printf("--------------------------\n");
}

void freeOrder(Order* pOrder)
{
	free(pOrder->customer->name);
	free(pOrder->customer);
	free(pOrder->date);
	free(pOrder->item->name);
	free(pOrder->item);
	free(pOrder);
}

////******************************************* text files *****************************************************

int readOrderFromTxtFile(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant, FILE* file)
{
	char temp[MAX_STR_LEN];
	if (!fgets(temp, MAX_STR_LEN, file))
		return 0;
	temp[strcspn(temp, "\n")] = '\0'; // Remove the newline character
	pOrder->item->name = getDynStr(temp);

	if (!fscanf(file, "%d\n%d\n%d\n", &pOrder->orderID, &pOrder->orderQuantity, &pOrder->orderPrice))
		return 0;

	if (!fgets(temp, MAX_STR_LEN, file))
		return 0;
	temp[strcspn(temp, "\n")] = '\0'; // Remove the newline character
	pOrder->customer->name = getDynStr(temp);

	if (!fscanf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		&pOrder->date->day, &pOrder->date->month, &pOrder->date->year, &pOrder->date->hour, &pOrder->date->minute, &pOrder->date->second))
		return 0;

	return 1;
}

int saveOrderToTxtFile(FILE* file, const Order* pOrder)
{
	if (!pOrder || !file)
		return 0;
	fprintf(file, "%s\n%d\n%d\n%d\n", pOrder->item->name, pOrder->orderID, pOrder->orderQuantity, pOrder->orderPrice);
	fprintf(file, "%s\n", pOrder->customer->name);
	fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n",
		pOrder->date->day, pOrder->date->month, pOrder->date->year, pOrder->date->hour, pOrder->date->minute, pOrder->date->second);
	return 1;
}

//******************************************* binary files *****************************************************
int readOrderFromBinFile(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant, FILE* file)
{
	if (!pOrder || !file)
		return 0;
	// Read the food item name
	pOrder->item->name = readStringFromFile(file, "");
	if (!pOrder->item->name)
		return 0;
	// Read the order ID, quantity, and price
	if (!fread(&pOrder->orderID, sizeof(int), 1, file))
		return 0;
	if (!fread(&pOrder->orderQuantity, sizeof(int), 1, file))
		return 0;
	if (!fread(&pOrder->orderPrice, sizeof(int), 1, file))
		return 0;
	// Read the customer name
	pOrder->customer->name = readStringFromFile(file, "Error reading order's customer name");
	if (!pOrder->customer->name)
		return 0;
	// Read the date
	if (!fread(pOrder->date, sizeof(Date), 1, file))
		return 0;

	return 1;
}

//**add String/int To Bin File functions in GeneralFiles**
int saveOrderToBinFile(FILE* file, const Order* pOrder)
{
	if (!pOrder || !file)
		return 0;
	// Save the food item name
	size_t len = strlen(pOrder->item->name) + 1;
	if (!fwrite(&len, sizeof(int), 1, file))
		return 0;
	if (!fwrite(pOrder->item->name, sizeof(char), len, file))
		return 0;
	// Save the order ID, quantity, and price
	if (!fwrite(&pOrder->orderID, sizeof(int), 1, file))
		return 0;
	if (!fwrite(&pOrder->orderQuantity, sizeof(int), 1, file))
		return 0;
	if (!fwrite(&pOrder->orderPrice, sizeof(int), 1, file))
		return 0;
	// Save the customer name
	len = strlen(pOrder->customer->name) + 1;
	if (!fwrite(&len, sizeof(int), 1, file))
		return 0;
	if (!fwrite(pOrder->customer->name, sizeof(char), len, file))
		return 0;
	// Save the date
	if (!fwrite(pOrder->date, sizeof(Date), 1, file))
		return 0;

	return 1;
}


