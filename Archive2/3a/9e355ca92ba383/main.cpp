#include <stdio.h>

int main()
{
char a[100];
int i = 0;
printf("Enter a number: ");
int res = scanf("%c", &a[i]);
if (res <= 0)
    printf("error");

printf("The number you've entered is: %d", a[i] - '0');
return 0;
} 