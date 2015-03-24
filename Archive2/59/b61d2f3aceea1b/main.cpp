#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define M 6

int main(void){
    int i=0,j=0,*a = malloc(sizeof(*a) * N * M);
    
    for(; i < N; ++i){
        for(; j < M; ++j){
            a[i][j] = (j+1)*(i+1);
        }
    }
    
    for(; i < N; ++i){
        for(; j < M; ++j){
            printf("%3d",a[i][j]);
        }
        printf("\n");
    }
    
    
	return 0;
}