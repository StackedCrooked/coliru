#include <stdio.h>

enum class e {one=1, two, three};

int main()
{
    e ee{}; // initializes ee to zero (not a valid value)
	printf("zero-initialized : %d\n", (int) ee);
	ee = e::one;
	printf("assigned 'one'   : %d\n", (int) ee);
}