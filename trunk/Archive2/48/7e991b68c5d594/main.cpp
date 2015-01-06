#include <stdio.h>


void foo(int, int (*)[*]);

void foo(int n, int (*pToVLA)[n])
{
    printf("%zu\n", sizeof *pToVLA);
}


int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	foo(sizeof a / sizeof a[0], &a);
	return 0;
}