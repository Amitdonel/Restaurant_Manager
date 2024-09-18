#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Admin.h"

const char* strAdminOptions[eNofAdminOptions] =
{ "Add Food Item", "Remove Food Item", "Edit Food Item", "Display Orders", "Process first Order","Display All Memberships", "Exit Admin Menu" };


int initAdmin(Admin* pAdmin)
{
	pAdmin->userName = "Admin";
	printf("User Name: %s\n", pAdmin->userName);
	getAdminCode(pAdmin->password);
	return 0;
}

int adminLogin(Admin* pAdmin)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do
	{
		ok = 1;
		printf("Admin Password (hint ---> %s ) : ", pAdmin->password);
		myGets(temp, MAX_STR_LEN);
		if (strcmp(temp, pAdmin->password) != 0)
		{
			printf("Wrong Password.. Please try again\n");
			ok = 0;
		}
	} while (!ok);
	return 1;
}

int getAdminCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do
	{
		ok = 1;
		printf("Please create a 3 characters Admin Password: ");
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != PASSWORD_LEN)
		{
			printf("Password should be %d characters\n", PASSWORD_LEN);
			ok = 0;
		}
	} while (!ok);

	strcpy(code, temp);
	return 1;
}

int adminMenu()
{
	int adminOption;
	printf("\nAdmin options:\n");
	for (int i = 0; i < eNofAdminOptions; i++)
	{
		printf("%d. %s\n", i, strAdminOptions[i]);
	}
	if (!scanf("%d", &adminOption))
		printf("Invalid input\n");

	CLEAR_BUFFER;
	return adminOption;
}
