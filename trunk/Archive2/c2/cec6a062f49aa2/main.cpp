#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define M 6

int main(void){
    int i=0,j=0,*a[N] = {NULL};
    
    for(; i < N; ++i){
        a[i] = malloc(sizeof(*a) * M);
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
    
    
	return 0;
}