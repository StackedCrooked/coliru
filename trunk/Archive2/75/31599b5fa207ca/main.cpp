// Elnoush C++ 2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>



void enter_info(int nop, int ID[50], char name[50][10], char family[50][20], int code[50], double mv[50], double income[50])
{
    printf("\nلطفا اطلاعات پزشکان را به ترتیب شماره پرسنلی، نام، نام خانوادگی، کد تخصص و مبلغ ویزیت وارد کنید\n");
	for (int i = 0; i < nop; i++)
	{
		printf("\n اطلاعات مربوط به پزشک %d", i + 1);
		scanf("%4d %c %c %2d %f6.2",
			&ID[i], &name[i], &family[i], &code[i], &mv[i]);
		income[i] = 0.00;
	}
	return;
}
void sort(int nop, int ID[50], char name[50][10], char family[50][20], int code[50], double mv[50], double income[50])
{

	//, sorted_name[50][10], sorted_family[50][20], sorted_code[50], sorted;
	char temp_family[20] = "", temp_name[20] = "";
	int ID_temp = 0, code_temp = 0;
	double mv_temp = 0, income_temp;

	for (int i = 0; i < nop - 1; i++)
	{
		for (int j = i + 1; j < nop; j++)
		{
			if (strcmp(family[i], family[j]) > 0)
			{
				strcpy(temp_name, name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j], temp_name);

				strcpy(temp_family, family[i]);
				strcpy(family[i], family[j]);
				strcpy(family[j], temp_family);

				ID_temp = ID[i];
				ID[i] = ID[j];
				ID[j] = ID_temp;

				code_temp = code[i];
				code[i] = code[j];
				code[j] = code_temp;

				mv_temp = mv[i];
				mv[i] = mv[j];
				mv[j] = mv_temp;

				income_temp = income[i];
				income[i] = income[j];
				income[j] = income_temp;
			}
		}
	}
	return;
}

void visit(int cd, int nop, int ID[50], char name[50][10], char family[50][20], int code[50], double mv[50], double income[50])
{
	int idp = 0;

	printf("\nاطلاعات پزشکان با کد تخصص داده شده از قرار زیر است\n");
	printf("  ID  ,    Name   ,        Family      , code ,    mv   ,    income    \n");

	for (int i = 0; i < nop; i++)
		if (code[i] == cd)
			printf(" %4d ,  %10c ,%20c, %2d , %f6.2  ,  %f10.2  \n",ID[i], name[i], family[i], code[i], mv[i], income[i]);

	printf("\nلطفا شماره پرسنلی پزشک موردنظر را وارد کنید\n");
	scanf("%4d", &idp);
	for (int i = 0; i < nop; i++)
	if (ID[i] == idp)
		income[i] += mv[i];

	return;
}

int vote(int idp, int nop, int ID[50], double mv[50], double income[50])
{
	int nazar = 4;

	printf("\nلطفا نظر خود را در مورد این پزشک اعلام نمایید\nبرای خوب عدد1\nبرای متوسط عدد0\n و برای بد عدد-1 را وارد کنید\n");
	scanf("%d", &nazar);
	switch (nazar)
	{
	case 1:
		for (int i = 0; i < nop; i++)
		if (ID[i] == idp)
			income[i] += mv[i] / 4;
		break;
	case 0:
		break;
	case -1:
		for (int i = 0; i < nop; i++)
		{
			if (ID[i] == idp)
			{
				income[i] -= mv[i] / 4;
				if (income[i] < 0)
				{
					income[i] = 0;
					return -1;
				}
			}
		}
		break;
	default:
		printf("\nعدد وارد شده درست نیست\n");
		break;
	}
	return 0;
}

void print_info(int nop, int ID[50], char name[50][10], char family[50][20], int code[50], double mv[50], double income[50])
{
	double max = 0.0;
	int andis = -1;

	printf("\nاطلاعات تمام پزشکان به شرح زیر است\n");
	printf("  ID  ,    Name   ,        Family      , code ,    mv   ,    income    \n");

	for (int i = 0; i < nop; i++)
		printf(" %4d ,  %10c ,%20c, %2d , %f6.2  ,  %f10.2  \n", ID[i], name[i], family[i], code[i], mv[i], income[i]);
	for (int i = 0; i < nop; i++)
		if (income[i]>max)
		{
			max = income[i];
			andis = i;
		}
	printf("\nاطلاعات پزشک با بیشترین درآمد به شرح زیر است\n");
	printf("  ID  ,    Name   ,        Family      , code ,    mv   ,    income    \n");
	printf(" %4d ,  %10c ,%20c, %2d , %f6.2  ,  %f10.2  \n", 
		ID[andis], name[andis], family[andis], code[andis], mv[andis], income[andis]);
}

int main()
{
	int n = 0, nop = 0, cd = 0, idp = 0;
	int ID[50], code[50];
	double mv[50], income[50];
	char name[50][10], family[50][20];

	printf("\nلطفا یک عدد از 1 تا 6 وارد کنید\n");
	printf("\nعدد 1 برای وارد کردن تعداد پزشکان و اطلاعات آنها\n");
	printf("\nعدد 2 برای مرتب کردن پزشکان بر اساس نام خانوادگی آنها\n");
	printf("\nعدد 3 برای وارد کردن کد تخصص و درخواست ملاقات با پزشک انتخاب شده\n");
	printf("\nعدد 4 برای نظرسنجی در مورد یک پزشک\n");
	printf("\nعدد 5 برای پرینت کردن اطلاعات پزشکان\n");
	printf("\nعدد 6 برای اتمام برنامه\n");

	while (scanf("%d", &n) != EOF)
	{
		switch (n)
		{
		case 1:
			printf("\nلطفا تعداد پزشکان را وارد کنید\n");
			scanf("%d", &nop);
			enter_info(nop, ID, name, family, code, mv, income);
			break;
		case 2:
			sort(nop, ID, name, family, code, mv, income);
			break;
		case 3:
			printf("\nلطفا کد پزشک را وارد کنید\n");
			scanf("%d", &cd);
			visit(cd, nop, ID, name, family, code, mv, income);
			break;
		case 4:
			printf("\nلطفا شماره پرسنلی پزشک را وارد کنید\n");
			scanf("%d", &idp);
			if (vote(idp, nop, ID, mv, income) == -1)
				printf("\nاین پزشک جزو پزشکان ضعیف این مرکز درمانی است\n");
			break;
		case 5:
			print_info(nop, ID, name, family, code, mv, income);
			break;
		case 6:
			return 0;
		default:
			printf("\nخطا: عدد ورودی باید یکی از اعداد 1 تا 6 باشد\n");
			break;
		}
		printf("\nلطفا یک عدد از 1 تا 6 وارد کنید\n");
	}

	return 0;
}

