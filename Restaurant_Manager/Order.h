#pragma once
#include "Customer.h"
#include "Date.h"
#include "General.h"
#include "GeneralFiles.h"
#include "Menu.h"
#include "Restaurant.h"


typedef struct
{
	int orderID;
	int orderQuantity;
	int orderPrice;
	foodItem* item;
	Customer* customer;
	Date* date;
}Order;

int			initOrder(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant);
Customer* initOrderCustomer(Restaurant* pRestaurant);
foodItem* initOrderFoodItem(Menu* pMenu);
Date* initOrderDate();
int			initOrderQuantity(Order* pOrder);
int			initOrderPrice(Order* pOrder);
int			initOrderID(Order* pOrder);
int			checkQuantity(Order* pOrder);
int			hasMemberShip();
int			compareOrdersByDate(const void* order1, const void* order2);
void		printOrder(const void* pOrder);
void		freeOrder(Order* pOrder);

int			readOrderFromTxtFile(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant, FILE* file);
int			saveOrderToTxtFile(FILE* file, const Order* pOrder);

int			readOrderFromBinFile(Order* pOrder, Menu* pMenu, Restaurant* pRestaurant, FILE* file);
int			saveOrderToBinFile(FILE* file, const Order* pOrder);


