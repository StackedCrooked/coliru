#include <cstdio>

int main(void){  
    int x = 2;  
    switch(x){  
        case 1: case 2: case 1: printf("Case 1 is executed");
        break;
        case 2: case 3: case 1: printf("Case 2 is executed");
        break;
        default : printf("Default case us execyted");
    }  
    return 0;  
    }