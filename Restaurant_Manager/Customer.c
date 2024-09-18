#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Customer.h"

int initCustomer(Customer* pCustomer)
{
	//init customer name
	pCustomer->name = getStrExactName("Enter your full name please: ");
	if (!pCustomer->name)
		return 0;

	//init customer ID
	time_t t;
	srand((unsigned)time(&t));
	pCustomer->customerID = rand() % 5000;
	return 1;
}

Customer* getCustomerById(Customer* customerArr, int numOfCustomer, int id)
{
	for (int i = 0; i < numOfCustomer; i++)
	{
		if (customerArr[i].customerID == id)
			return &customerArr[i];
	}
	return NULL;
}

void printCustomer(const Customer* pCustomer, int index)
{
	printf("|----------------------|-------|\n");
	printf("| %-20s | %-5d |\n", pCustomer->name, pCustomer->customerID);
	printf("|----------------------|-------|\n");
}

void freeCustomer(Customer* pCustomer, int index)
{
	free(pCustomer->name);
}

////******************************************* text files *****************************************************

int saveCustomerToTxtFile(const Customer* pCustomer, FILE* fp)
{
	if (!fp || !pCustomer)
		return 0;

	fprintf(fp, "%s\n%d\n", pCustomer->name, pCustomer->customerID);
	return 1;
}

int readCustomerFromTxtFile(Customer* pCustomer, FILE* fp)
{
	if (!fp || !pCustomer)
		return 0;

	char temp[MAX_STR_LEN];
	if (!fgets(temp, MAX_STR_LEN, fp))
		return 0;
	temp[strcspn(temp, "\n")] = 0;
	pCustomer->name = getDynStr(temp);
	if (!pCustomer->name)
		return 0;
	if (!fscanf(fp, "%d\n", &pCustomer->customerID))
		return 0;
	return 1;
}

////******************************************* binary files *****************************************************
int saveCustomerToBinFile(const Customer* pCustomer, FILE* fp)
{
	size_t len = strlen(pCustomer->name) + 1;
	if (!fwrite(&len, sizeof(int), 1, fp))
		return 0;
	if (!fwrite(pCustomer->name, sizeof(char), len, fp))
		return 0;

	if (!fwrite(&pCustomer->customerID, sizeof(int), 1, fp))
		return 0;

	return 1;
}

int readCustomerFromBinFile(Customer* pCustomer, FILE* fp)
{
	if (!fp || !pCustomer)
		return 0;

	pCustomer->name = readStringFromFile(fp, "Error reading customer name");
	if (!pCustomer->name)
		return 0;
	fread(&pCustomer->customerID, sizeof(int), 1, fp);

	return 1;
}





