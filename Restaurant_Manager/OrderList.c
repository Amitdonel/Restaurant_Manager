#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "OrderList.h"

int initOrderList(OrderList* pOrderList)
{
	if (!L_init(&pOrderList->orderList))
		return 0;
	return 1;
}

int placeOrder(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant)
{
	Order* pOrder = (Order*)calloc(1, sizeof(Order));
	if (!pOrder)
		return 0;

	if (!initOrder(pOrder, pMenu, pRestaurant))
	{
		freeOrderList(pOrderList);
		free(pOrder);
		return 0;
	}

	if (!L_insert(&pOrderList->orderList.head, pOrder, compareOrdersByDate))
	{
		freeOrder(pOrder);
		return 0;
	}

	printf("\nOrder placed successfully for %s!\n", pOrder->customer->name);
	return 1;
}

int processOrder(OrderList* pOrderList)
{
	if (!L_delete(&pOrderList->orderList.head, free))
	{
		printf("No orders to process!\n");
		return 0;
	}
	printf("\n=============================================================\n");
	printf("Processing first order");
	for (int i = 0; i < 10; ++i)
	{
		printf(".");
		fflush(stdout);
		Sleep(300); // Introduce a delay of 500,000 microseconds (0.5 seconds) between dots
	}
	printf("\n");
	printf("Order has been processed successfully!\n");
	return 1;
}

void printOrderList(const OrderList* pOrderList)
{
	printf("\n=============================================================");
	printf("\n                   O r d e r   L i s t			           \n");
	printf("=============================================================\n");
	if (!L_print(&pOrderList->orderList, printOrder))
		printf("|                  No Order items found!                      |\n");
	printf("\n=============================================================\n");

}

void freeOrderList(OrderList* pOrderList)
{
	L_free(&pOrderList->orderList, freeOrder);
}

Order* createOrderFromFile()
{
	Order* pOrder = (Order*)calloc(1, sizeof(Order));
	if (!pOrder)
		return NULL;
	pOrder->item = (foodItem*)calloc(1, sizeof(foodItem));
	pOrder->customer = (Customer*)calloc(1, sizeof(Customer));
	pOrder->date = (Date*)calloc(1, sizeof(Date));
	return pOrder;
}

//******************************************* text files *****************************************************

int initOrderListFromTxtFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "r");
	CHECK_FILE_INIT(file)

		if (!readOrdersFromTxtFile(pOrderList, pMenu, pRestaurant, file))
		{
			fclose(file);
			return 0;
		}
	return 1;
}

int readOrdersFromTxtFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, FILE* file)
{
	if (!L_init(&pOrderList->orderList))
	{
		fclose(file);
		return 0;
	}
	while (!feof(file))
	{
		Order* pOrder = createOrderFromFile();
		if (!pOrder)
			return 0;

		if (!readOrderFromTxtFile(pOrder, pMenu, pRestaurant, file))
		{
			freeOrder(pOrder);
			return 0;
		}
		if (!L_insert(&pOrderList->orderList.head, pOrder, compareOrdersByDate))
		{
			freeOrder(pOrder);
			return 0;
		}
	}
	return 1;
}

int saveOrderListToTxtFile(const OrderList* pOrderList, const char* fileName)
{
	FILE* file = fopen(fileName, "w");
	CHECK_FILE_SAVE(file);

	if (!L_save(&pOrderList->orderList, file, saveOrderToTxtFile))
	{
		fclose(file);
		return 0;
	}
	return 1;
}

//******************************************* Binary files ****************************************************

int initOrderListFromBinFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "rb");
	CHECK_FILE_INIT(file)
		if (!readOrdersFromBinFile(pOrderList, pMenu, pRestaurant, file))
		{
			fclose(file);
			return 0;
		}
	return 1;
}

int readOrdersFromBinFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, FILE* file)
{
	if (!L_init(&pOrderList->orderList))
	{
		fclose(file);
		return 0;
	}
	while (1)
	{
		Order* pOrder = createOrderFromFile();
		if (!pOrder)
			return 0;
		if (!readOrderFromBinFile(pOrder, pMenu, pRestaurant, file))
		{
			freeOrder(pOrder);
			break;
			return 0;
		}
		if (!L_insert(&pOrderList->orderList.head, pOrder, compareOrdersByDate))
		{
			freeOrder(pOrder);
			return 0;
		}
	}
	return 1;
}

int saveOrderListToBinFile(const OrderList* pOrderList, const char* fileName)
{
	FILE* file = fopen(fileName, "wb");
	CHECK_FILE_SAVE(file);

	if (!L_save(&pOrderList->orderList, file, saveOrderToBinFile))
	{
		fclose(file);
		return 0;
	}
	return 1;
}


