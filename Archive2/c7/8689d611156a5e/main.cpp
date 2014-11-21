#include <stdio.h>

int main()
{
    printf("Insert three numbers \n" );
	int num1,num2,num3;
	scanf("%d %d %d" ,num1, num2, num3);
	printf("Your average is: %f" ,num1+num2+num3 /3.0);
	return (0);
}