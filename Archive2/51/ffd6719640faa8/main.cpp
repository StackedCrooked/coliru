#include <stdio.h>

#define M 5
#define N 4

typedef union {
    int a1[M * N];
    int a2[M][N];
} U;

int main()
{
    U u;
    int i, j;

    for (i = 0; i < M * N; ++i)
    {
        u.a1[i] = i;
    }

    for (i = 0; i < M; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            printf("%8d", u.a2[i][j]);
        }
        printf("\n");
    }

    return 0;
}

