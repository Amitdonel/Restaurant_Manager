#include <stdio.h>
#include <stdlib.h>
#include "Restaurant.h"

int initRestaurant(Restaurant* pRestaurant)
{
	pRestaurant->CustomerArr = NULL;
	pRestaurant->numOfCustomers = 0;
	initAdmin(&pRestaurant->admin);
	return 1;
}

int addCustomer(Restaurant* pRestaurant)
{
	printf("Please Enter Your Customer Details\n\n");
	Customer* temp =
		(Customer*)realloc(pRestaurant->CustomerArr, (pRestaurant->numOfCustomers + 1) * sizeof(Customer));
	if (!temp)
		return 0;
	pRestaurant->CustomerArr = temp;

	if (!pRestaurant->CustomerArr)
		return 0;

	initCustomer(&pRestaurant->CustomerArr[pRestaurant->numOfCustomers]);
	printf("Customer added successfully..\n");
	printf("New Customer ID: %d\n", pRestaurant->CustomerArr[pRestaurant->numOfCustomers].customerID);
	pRestaurant->numOfCustomers++;
	return 0;
}

Customer* findACustomer(Restaurant* pRestaurant)
{
	if (!displayAllCustomers(pRestaurant))
		return NULL;
	int id;
	Customer* temp;
	do {
		printf("Please enter your customer ID:");
		if (!scanf("%d", &id))
		{
			printf("Invalid input\n");
			return NULL;
		}

		temp = getCustomerById(pRestaurant->CustomerArr, pRestaurant->numOfCustomers, id);
		if (!temp)
			printf("Customer ID not found, please try again.\n");
		//clear buffer
		CLEAR_BUFFER;
	} while (!temp);

	return temp;
}

int displayAllCustomers(const Restaurant* pRestaurant)
{
	if (!pRestaurant->CustomerArr)
	{
		printf("No Customers to display.\n");
		return 0;
	}
	printf("All Customers:\n");
	printf("|----------------------|-------|\n");
	printf("| %-20s | %-5s |\n", "Name", "ID");
	generalArrayFunction((void*)pRestaurant->CustomerArr, pRestaurant->numOfCustomers, sizeof(Customer), printCustomer);
	return 1;
}

void freeRestaurant(Restaurant* pRestaurant)
{
	if (pRestaurant->CustomerArr)
	{
		generalArrayFunction((void*)pRestaurant->CustomerArr, pRestaurant->numOfCustomers, sizeof(Customer), freeCustomer);
		free(pRestaurant->CustomerArr);
	}
	pRestaurant->numOfCustomers = 0;
}

int allocateMemoryForCustomers(Restaurant* pRestaurant, int numOfCustomers)
{
	pRestaurant->numOfCustomers = numOfCustomers;
	pRestaurant->CustomerArr = (Customer*)malloc(numOfCustomers * sizeof(Customer));
	if (!pRestaurant->CustomerArr)
	{
		printf("Error allocating memory for customers\n");
		return 0;
	}
	return 1;
}

//******************************************* text files *****************************************************
int initRestaurantFromTxtFile(Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "r");
	CHECK_FILE_INIT(file);
	int count = 0;
	if (!readItemCountFromTxtFile(file, &count))
	{
		fclose(file);
		return 0;
	}
	if (!allocateMemoryForCustomers(pRestaurant, count))
	{
		fclose(file);
		return 0;
	}
	if (!readCustomersFromTxtFile(pRestaurant, file))
	{
		fclose(file);
		return 0;
	}
	initAdmin(&pRestaurant->admin);
	fclose(file);
	return 1;
}

int readCustomersFromTxtFile(Restaurant* pRestaurant, FILE* file)
{
	for (int i = 0; i < pRestaurant->numOfCustomers; i++)
	{
		if (!readCustomerFromTxtFile(&pRestaurant->CustomerArr[i], file))
		{
			printf("Error reading customer from file\n");
			return 0;
		}
	}
	return 1;
}

int saveRestaurantToTxtFile(const Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "w");
	CHECK_FILE_SAVE(file);
	int count = pRestaurant->numOfCustomers;
	fprintf(file, "%d\n", count);
	for (int i = 0; i < count; i++)
		saveCustomerToTxtFile(&pRestaurant->CustomerArr[i], file);

	fclose(file);
	return 1;
}

//******************************************* binary files *****************************************************
int initRestaurantFromBinFile(Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "rb");
	CHECK_FILE_INIT(file);
	int count = 0;
	if (!readItemCountFromBinFile(file, &count))
	{
		fclose(file);
		return 0;
	}
	if (!allocateMemoryForCustomers(pRestaurant, count))
	{
		fclose(file);
		return 0;
	}
	if (!readCustomersFromBinFile(pRestaurant, file))
	{
		fclose(file);
		return 0;
	}
	initAdmin(&pRestaurant->admin);
	return 1;
}

int readCustomersFromBinFile(Restaurant* pRestaurant, FILE* file)
{
	for (int i = 0; i < pRestaurant->numOfCustomers; i++)
	{
		if (!readCustomerFromBinFile(&pRestaurant->CustomerArr[i], file))
		{
			printf("Error reading customer from file\n");
			return 0;
		}
	}
	return 1;
}

int saveRestaurantToBinFile(const Restaurant* pRestaurant, const char* fileName)
{
	FILE* file = fopen(fileName, "wb");
	CHECK_FILE_SAVE(file);

	int count = pRestaurant->numOfCustomers;
	fwrite(&count, sizeof(int), 1, file);
	for (int i = 0; i < count; i++)
		saveCustomerToBinFile(&pRestaurant->CustomerArr[i], file);

	fclose(file);
	return 1;
}


