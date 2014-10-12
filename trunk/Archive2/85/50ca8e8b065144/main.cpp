#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int mat[5][5]; int res; } graphe;

int main(void) {
int m[5][5]={{0,1,1,1,0},{1,0,1,1,0},{1,1,0,1,1},{1,1,1,0,1},{0,0,1,1,0}};
graphe g;
memcpy( g.mat, m, sizeof(m));

int i,j;
for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            printf("%i ",g.mat[i][j]);
        }
        printf("\n");
    }
printf("Res = %i ",g.res);
    return 0;
}

