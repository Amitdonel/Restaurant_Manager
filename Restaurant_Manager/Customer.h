#pragma once
#include "General.h"
#include "GeneralFiles.h"

typedef struct
{
	char* name;
	int customerID;
}Customer;

int			initCustomer(Customer* pCustomer);
void		printCustomer(const Customer* pCustomer, int index);
Customer*	getCustomerById(Customer* pCustomer, int numOfCustomer, int id);
void		freeCustomer(Customer* pCustomer, int index);

int			readCustomerFromTxtFile(Customer* pCustomer, FILE* fp);
int			saveCustomerToTxtFile(const Customer* pCustomer, FILE* fp);

int			readCustomerFromBinFile(Customer* pCustomer, FILE* fp);
int			saveCustomerToBinFile(const Customer* pCustomer, FILE* fp);