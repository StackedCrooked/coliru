#include <stdio.h>
#include <stdlib.h>

#define MAXR 2
#define MAXC 3

void caricaMatrice(int M[][MAXC]){
    int r,c;
    for(r=0;r<MAXR;r++){
        for (c=0;c<MAXC;c++){
            printf("Elemento [%d][%d]:",r,c);
            scanf("%d",&M[r][c]);
        }
    }
}

void visMatrice(int M[][MAXC]){
    int r,c;
    for(r=0;r<MAXR;r++){
        for (c=0;c<MAXC;c++){
            printf("%3d ",M[r][c]);
        }
        printf("\n");
    }
}


int main(){
    int mat[MAXR][MAXC];

    caricaMatrice(mat);
    visMatrice(mat);
    return 0;
}
