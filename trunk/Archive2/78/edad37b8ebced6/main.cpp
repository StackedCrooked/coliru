#include <cstdio>

int main()
{
    int lignes = 5;
    
    typedef struct { int mat[5][5]; int res; } graphe;
    
    int m[5][5]={{0,1,1,1,0},{1,0,1,1,0},{1,1,0,1,1},{1,1,1,0,1},{0,0,1,1,0}};
    graphe g = { m[5][5], 5};
    
    for(int i=0;i<lignes;i++)
    {
        for(int j=0;j<lignes;j++)
        {
            printf("%i ",g.mat[i][j]);
        }
        printf("\n");
    }
}