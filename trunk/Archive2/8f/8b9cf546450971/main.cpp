#include <string.h>
#include <stdio.h>
char str[] = "Hello World";
char *ptr;

ptr =  strchr(str, 'W');
printf("%s\n", ptr);