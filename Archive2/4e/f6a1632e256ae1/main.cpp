#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4


int main(void){
    int M=6;
    int i=0,j=0,*a[N] = {NULL};
    
    for(; i < N; ++i){
        a[i] = malloc(sizeof(int) * M);
        for(j=0; j < M; ++j){
            a[i][j] = (j+1)*(i+1);
        }
    }
    
    for(i=0; i < N; ++i){
        for(j=0; j < M; ++j){
            printf("%3d",a[i][j]);
        }
        printf("\n");
    }
    
    for(i=0; i < N; ++i){
        free(a[i]);
    }
    
    
	return 0;
}