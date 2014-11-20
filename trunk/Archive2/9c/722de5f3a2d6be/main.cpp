#include <stdio.h>

int main()

{
    

    int n, sum = 0, c, value;
	n = 10;
	int max = 0;
	int min = 0;



	printf("Write 10 numbers\n");

	for (c = 1; c <= n; c++)
	{
		scanf_s("%d", &value);
		

		if (c = 1)
		{
			max = value;
			min = value;

			
		}
		else if (value < max, c <= n)
		{
			max = value;
		}

		else if (value < min, c <= n)
		{
			min = value;
		}
	}

	printf("Biggest number is : %d\n", max);
	printf("Smallest number is : %d\n", min);



	return 0;
}
