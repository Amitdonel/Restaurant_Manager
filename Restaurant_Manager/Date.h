#pragma once

typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} Date;

int		initDate(Date* pDate);
void	printDate(const Date* pDate);


