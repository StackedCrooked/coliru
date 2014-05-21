#include <stddef.h>
#include <stdio.h>

int main(void)
{
    size_t n=10;

    printf("Please input `n': ");
    scanf("%zu", &n);

    int matrix[n][n];

    for (size_t i=0; i < n; ++i)
        for (size_t j=0; j < n; ++j)
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;

    for (size_t i=0; i < n; ++i)
    {
        for (size_t j=0; j < n; ++j)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }
}