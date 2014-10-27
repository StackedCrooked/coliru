#include <stdio.h>
#include <stdlib.h>

typedef int (*intFunction)(int,int);  

typedef struct {
    int value;
    intFunction func;
} ValueFunc;

int addInts(int a, int b){
    return a + b;
}

int main(){
    ValueFunc vf;
    vf.value = 3;
    vf.func = &addInts;
    int y = vf.func(vf.value,4);
    printf("%i",y);
    free(vf.func);
    return 0;
}