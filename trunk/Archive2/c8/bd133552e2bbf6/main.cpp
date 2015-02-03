#include <stdio.h>
#include <string.h>
int main (void)
{
    char myString[11] = {'z','l','a','t','a','n',0}; 
	char myOtherString[19]={0};
	printf("The string length is %d!\n",strlen(myString));
	strcpy(myOtherString,myString);
	strcat(myOtherString," ibraimovich");
	printf("The second string is %s\tand its length is %d.\n",myOtherString,strlen(myOtherString));
	return 0;
}

