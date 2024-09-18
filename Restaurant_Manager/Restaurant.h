#pragma once
#include "Customer.h"
#include "General.h"
#include "GeneralFiles.h"
#include "Admin.h"

typedef struct
{
	Customer* CustomerArr;
	int numOfCustomers;
	Admin admin;
}Restaurant;


int			initRestaurant(Restaurant* pRestaurant);
void		freeRestaurant(Restaurant* pRestaurant);

int			addCustomer(Restaurant* pRestaurant);
Customer* findACustomer(Restaurant* pRestaurant);
int			displayAllCustomers(const Restaurant* pRestaurant);

int			allocateMemoryForCustomers(Restaurant* pRestaurant, int numOfCustomers);

int			initRestaurantFromTxtFile(Restaurant* pRestaurant, const char* fileName);
int			readCustomersFromTxtFile(Restaurant* pRestaurant, FILE* file);
int			saveRestaurantToTxtFile(const Restaurant* pRestaurant, const char* fileName);

int			initRestaurantFromBinFile(Restaurant* pRestaurant, const char* fileName);
int			readCustomersFromBinFile(Restaurant* pRestaurant, FILE* file);
int			saveRestaurantToBinFile(const Restaurant* pRestaurant, const char* fileName);