#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 4

typedef int Array1D[M * N];
typedef int Array2D[M][N];

int main()
{
    Array1D *a1 = (Array1D *)malloc(sizeof(*a1));
    Array2D *a2 = (Array2D *)a1;
    int i, j;
    
    for (i = 0; i < M * N; ++i)
    {
        (*a1)[i] = i;
    }

    for (i = 0; i < M; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            printf("%8d", (*a2)[i][j]);
        }
        printf("\n");
    }

    free(a1);
    
    return 0;
}

