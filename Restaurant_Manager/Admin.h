#pragma once
#include "General.h"

#define PASSWORD_LEN 3
#define MAX_STR_LEN 255

typedef enum
{
	eAddFoodItem, eRemoveFoodItem, eEditFoodItem, eDisplayOrders, eProcessFirstOrder, eDisplayAllCustomers, eAdminExit, eNofAdminOptions
}eAdminOptions;

const extern char* strAdminOptions[eNofAdminOptions];

typedef struct
{
	char* userName;
	char password[PASSWORD_LEN];
}Admin;

int		initAdmin(Admin* pAdmin);
int		getAdminCode(char* code);
int		adminMenu();
int		adminLogin(Admin* pAdmin);
