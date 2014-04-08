#include <stdio.h>
#include <stdlib.h>

void foo(int*);
int main(void){
    int *k = NULL;
    foo(k);
    printf("%p\n", k);
    printf("%d\n", *k);
    return 0;
}

void foo(int *i){
    i = malloc(sizeof(int));
    if (i == NULL){
        printf("memory fail\n");
    }else {
        *i = 10;
    }
}