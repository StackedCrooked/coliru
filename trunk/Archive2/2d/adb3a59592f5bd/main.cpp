#include <string.h>
#include <stdio.h>

int main()
{
	char str2[30] = "\052";
	char str3[30] = "\05";
    
    int a = strlen(str2);
    int b = strlen(str3);

	printf("Length of str %d\n", a);
	printf("Length of str %d\n", b);

	return 0;
}