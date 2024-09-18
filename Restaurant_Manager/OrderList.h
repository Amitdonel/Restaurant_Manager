#pragma once
#include "List.h"
#include "Order.h"
#include "Menu.h"
#include "General.h"

typedef struct
{
	LIST orderList;
}OrderList;

int		initOrderList(OrderList* pOrderList);
int		placeOrder(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant);
int		processOrder(OrderList* pOrderList);
void	printOrderList(const OrderList* pOrderList);
void	freeOrderList(OrderList* pOrderList);
Order* createOrderFromFile();

int		initOrderListFromTxtFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, const char* fileName);
int		readOrdersFromTxtFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, FILE* file);
int		saveOrderListToTxtFile(const OrderList* pOrderList, const char* fileName);

int		initOrderListFromBinFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, const char* fileName);
int		readOrdersFromBinFile(OrderList* pOrderList, Menu* pMenu, Restaurant* pRestaurant, FILE* file);
int		saveOrderListToBinFile(const OrderList* pOrderList, const char* fileName);