#include <stdio.h>

int main()
{
    int matrix1[50][50];
    int matrix2[50][50];
    
    for(int i = 0; i < 50; ++i)
    {
        for(int j = 0; j < 50; ++j)
            matrix1[i][j] = i + j;
    }
    
    printf("Valores da matrix A\n");
    for(int i = 0; i < 50; ++i)
    {
        for(int j = 0; j < 50; ++j)
            printf("%d ", matrix1[i][j]);
        printf("\n");
    }
    
    for(int i = 0; i < 50; ++i)
    {
        for(int j = 0; j < 50; ++j)
        {
            if(i == j)
                matrix2[i][j] = matrix1[i][j] * 3;
            else
                matrix2[i][j] = matrix1[i][j] * 2;
        }
    }
    

    printf("\nValores da matrix B\n");
    for(int i = 0; i < 50; ++i)
    {
        for(int j = 0; j < 50; ++j)
            printf("%d ", matrix2[i][j]);
        printf("\n");
    }
    
    return 0;
}
