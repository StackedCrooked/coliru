#include <stdio.h>

int main()
{
    printf("Addition calculator\n");
    int num1,num2;
    printf("Enter the first number: ");
    scanf(" %d",num1);
    printf("\nEnter the second number: ");
    scanf(" %d",num2);
    int sol;
    sol=num1+num2;
    printf("The solution is %d", sol);
    return(0);
}
