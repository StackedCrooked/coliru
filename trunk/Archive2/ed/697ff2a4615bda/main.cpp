#include <omp.h>
#include <iostream>

int main()
{
    int id = 0;
#pragma omp parallel
    {
        int m = 5000;
        std::cout << "parallel section #" << ++id << "\n";

        {
#pragma omp single
            std::cout << "first single section\n";
            for (int j=0; j<m; ++j)
            {
            }
        }

        {
#pragma omp single
            std::cout << "second single section\n";
            for (int j=m; j<2*m; ++j)
            {
            }
        }

    }
}