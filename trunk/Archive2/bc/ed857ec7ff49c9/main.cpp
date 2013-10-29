#include <stdio.h>

int main(){
    int x; 
    int i = 9; 
    int array[i]; 

    for(x = 0; x < i; x++)
        printf("%d\n", array[x]);

    return 0; 
}