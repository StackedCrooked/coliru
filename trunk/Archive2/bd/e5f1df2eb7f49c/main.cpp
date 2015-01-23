#include <stdio.h>

int main(){
    int A[3][2] = {0} ;
    int AT[2][3] = {0} ;  // <<<

    printf("A = \n");   
    for(int x = 0 ; x < 3 ; x++){
        for (int y = 0 ; y < 2 ; y ++){
            A[x][y] = (x+1)*1 + (x*1+3)*y ; 
            printf("A[%d][%d] = %d ", x , y ,A[x][y]);
        }
        printf("\n");
    }   
    printf("\nAT = \n");    
    for (int p = 0 ; p < 2 ; p++){
        for (int q = 0 ; q < 3 ; q++){
            AT[p][q] = A[q][p]; // <<<
            printf("A[%d][%d] = %d ", p ,q , AT[p][q]);
        }
        printf("\n");
    }
    return 0;
}