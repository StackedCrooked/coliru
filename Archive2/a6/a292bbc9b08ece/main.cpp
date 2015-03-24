#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int ROW = 4;
    int COLUMN = 6;
    int i=0,j=0, **a = malloc(sizeof(int*) * ROW /* The memory for the pointers*/ + ( (sizeof(int) * ROW) * COLUMN) /* The memory for the data*/ );    

    int *data = (int*)(a + ROW);
    for(i = 0; i < ROW; ++i){  // we need to initialize each of of our row pointers to point to the correct row otherwise bad things wil happaen :)
        a[i] = data + i * COLUMN;
    }
    // done, now we can use it
        
    for(i=0; i < ROW; ++i){
        for(j=0; j < COLUMN; ++j){
            a[i][j] = (j+1)*(i+1);
        }
    }
    
    for(i=0; i < ROW; ++i){
        for(j=0; j < COLUMN; ++j){
            printf("%3d",a[i][j]);
        }
        printf("\n");
    }
    
    free(a);
    
	return 0;
}