#include <stdio.h>
#include <time.h>
#include "Date.h"

int initDate(Date* pDate)
{
	if (pDate == NULL)
		return 0;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	pDate->year = tm.tm_year + 1900;
	pDate->month = tm.tm_mon + 1;
	pDate->day = tm.tm_mday;
	pDate->hour = tm.tm_hour;
	pDate->minute = tm.tm_min;
	pDate->second = tm.tm_sec;
	return 1;
}

void printDate(const Date* pDate)
{
	if (pDate == NULL)
	{
		printf("Date is not initialized\n");
		return;
	}
	printf("%02d/%02d/%d\t", pDate->day, pDate->month, pDate->year);
	printf("%02d:%02d:%02d\n", pDate->hour, pDate->minute, pDate->second);
}
