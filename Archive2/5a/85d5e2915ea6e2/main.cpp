#include <stdlib.h>

void allocate(double (**grid)[], size_t cols, size_t rows)
{
    int (*p)[cols];
	*grid = malloc(rows * sizeof *p);
}

int main()
{
	size_t n = 3, k = 5;
	int (*p)[n];
	allocate(&p, n, k);
	return 0;
}