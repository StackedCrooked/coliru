#include <iostream>
#include <cmath>
#include <limits>

#define N 5

void distanza(bool *SOL, int k, int n, int d, int min, int presi)
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
            
            int newMin;
            
            if (i == 1 && (k + 1) < min)
            {
                newMin = k + 1;
            }
            else
            {
                newMin = min;
            }

			SOL[k] = (i ? true : false);
            
            if (k + 1 - min <= d || presi + i <= 2)
            {
                distanza(SOL, k + 1, n, d, newMin, presi + i);
            }

		}

	}


}

int main(int argc, char *argv[])
{

	bool SOL[N];
	distanza(SOL, 0, N, 2, std::numeric_limits<int>::max(), 0);
	return 0;

}