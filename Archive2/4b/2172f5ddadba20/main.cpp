#include <omp.h>

int main()
{
    for (int i=0; i <100; ++i)
    {
        int m = 5000;

#pragma omp parallel for 
        for (int j=0; j<m; ++j)
        {
        }

#pragma omp parallel for 
        for (int j=m; j<2*m; ++j)
        {
        }

    }
}