#include <cstdio>

int main()
{
    int x = 1;
	float sum = 0;
	int i;
	for (i = 1; i <= 20; i++){
		sum = 1.0f / (x)+sum;
		x = x * 2;
	}
	printf("sum=%f", sum);
	printf("\n");
	return 0;
}