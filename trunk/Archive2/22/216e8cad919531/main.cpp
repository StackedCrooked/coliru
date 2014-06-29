#include <iostream>
#include <cmath>

#define N 5

void sottoinsiemi(bool *SOL, int k, int n, int dispari_presi)
{

    if (k == n)
	{
		for (int i = 0; i < n; i++)
		{

			if (SOL[i])
			{
				std::cout << (i + 1) << " ";
			}

		}

		std::cout << std::endl;

	}
	else
	{

		for (int i = 0; i <= 1; i++)
		{

			SOL[k] = (i ? true : false);

			int dispari_rimanenti = (int) ceil ((n - (k + 1)) / 2);

			int m = ((k + 1) % 2 != 0 && i == 1 ? 1 : 0);

			if (dispari_presi + m + dispari_rimanenti >= 2)
			{
				sottoinsiemi(SOL, k + 1, n, dispari_presi + m);
			}

		}

	}


}

int main(int argc, char *argv[])
{

	bool SOL[N];
	sottoinsiemi(SOL, 0, N, 0);
	return 0;

}