#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>

#define DIM 1000
#define ITERATIONS 100

#define CPU_START clock_t t1; t1=clock();
#define CPU_END {long int final=clock()-t1; printf("CPU took %li ticks (%f seconds) \n", final, ((float)final)/CLOCKS_PER_SEC);}

int main(void)
{
    double ** d_matrix, ** d_res_matrix;

    d_res_matrix = new double * [DIM];
    d_matrix = new double * [DIM];

    for (int i = 0; i < DIM; i++)
    {
        d_matrix[i] = new double [DIM];
        d_res_matrix[i] = new double[DIM];
    }

    d_matrix[20][45] = 1; // start somewhere

    double f0, f1, f2, f3, f4;

    CPU_START;

    for (int iter = 0; iter < ITERATIONS; iter++)
    {
        for (int x = 1; x < DIM-1; x++) // avoid boundary cases for this example
        {
            for (int y = 1; y < DIM-1; y++)
            {
                f0 = d_matrix[x][y];
                f1 = d_matrix[x-1][y];
                f2 = d_matrix[x+1][y];
                f3 = d_matrix[x][y-1];
                f4 = d_matrix[x][y+1];

                double a = f0*0.6 + f1*0.1 + f2*0.1 + f3*0.1 + f4*0.1;

                // THIS PART IS INTERESTING:
                //d_res_matrix[x][y] = a;
                d_res_matrix[x][y] = a + 0.000000001;

            }
        }
        for (int x = 1; x < DIM-1; x++)
        {
            for (int y = 1; y < DIM-1; y++)
            {
                d_matrix[x][y] = d_res_matrix[x][y];
            }
        }
    }
    CPU_END; 

    return 0;
}