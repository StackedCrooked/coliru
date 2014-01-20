#include<stdio.h>
#include<string.h>

int main()
{
 char str[50] = "Hello World";
 char *ptr1 = strchr(str, 'H');
 char *ptr2 = strchr(str, 'e');
 char *ptr3 = strchr(str, 'l');
 printf("%u\n%u\n%u\n", ptr1,ptr2,ptr3);
 
  return 0;
}