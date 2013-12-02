#include <stdlib.h>
#include <stdio.h>
int main()
{
int size_of_array = 10;
printf("%d\n", size_of_array);
char** array;
printf("hello");
array = (char**)malloc(sizeof(char*)*size_of_array);
}
