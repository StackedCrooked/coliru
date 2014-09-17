#include <stdio.h>
#include <stdlib.h>

const int ERROR = 1;
const int SUCCESS = 0;

#define WITH_ALLOC(T,X,FN) \
    T* X = malloc(sizeof(X)); \
    int fn() { \
        FN \
        return SUCCESS; \
    } \
    fn (); \
    free(X);


int main() {
    WITH_ALLOC(int, x, {
        *x = 5;
        
        if (*x == 5) 
            return ERROR;
            
        printf("%d", *x);
    })
}