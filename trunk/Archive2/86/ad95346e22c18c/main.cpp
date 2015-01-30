#include <stdio.h>
#include <string.h>

void print_array(char array[], int size)
{
    int i;
	for (i = 0; i < size; i++)
	{
		printf("%c\n", array[i]);
	}
}

int main(void)
{
    char args[5] = {'a','b','c','d','e'} ;

	char tail[4] = {0};
	memcpy(tail, &args[1], sizeof(tail));	

	print_array(tail, sizeof(tail));
}