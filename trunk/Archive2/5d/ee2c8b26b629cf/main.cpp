#include <stdio.h>
 
// Same as "void print(int **arr, int m, int n)"
void print(int *arr[], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
        printf("%d ", *((arr+i*n) + j));
}
 
int main()
{
    int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int m = 3;
    int n = 3;
    print((int **)arr, m, n);
    return 0;
}