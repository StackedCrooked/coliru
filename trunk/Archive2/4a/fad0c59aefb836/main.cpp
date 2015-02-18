#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char** Allocate2DArray(int rows, int nCols)
{
    int i;
	char** retValue = (char**)malloc(rows * sizeof(char*));
	char* pool = (char*)malloc(rows * nCols * sizeof(char));
	for (i = 0; i < rows; ++i, pool += nCols)
		retValue[i] = pool;
	return retValue;
}

int fillWithNames(char*** namesin, int *n)
{
	char **temp = Allocate2DArray(4, 100);
	int i;
	char buf[20];
	for (i = 0; i < 4; ++i)
	{
		sprintf(buf, "Testing %d", i);
		strcpy(temp[i], buf);
	}
	*namesin = temp;
	*n = 4;
	return 1;
}

void printTheNames(char*** names, int n)
{
	int i;
	char **ptr1 = names[0];
	for (i = 0; i < n; ++i)
		printf("%s\n", ptr1[i]);
}

int main()
{
	char** test; int n;
	fillWithNames(&test, &n);
	printTheNames(&test, n);
	free(test[0]);
	free(test);
}