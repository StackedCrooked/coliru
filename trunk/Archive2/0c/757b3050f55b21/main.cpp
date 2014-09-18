#include <stdio.h>
#include <stdlib.h>

const int ERROR = 1;
const int SUCCESS = 0;

#define WITH_ALLOC(T,X,FN) \
    T* X = malloc(sizeof(T)); \
    do { \
        FN \
        return SUCCESS; \
    } while (0); \
    free(X);


int main() {
    WITH_ALLOC(int, x, {
        *x = 5;
        
        printf("%d", *x);
        
        if (*x == 5) 
            break;
            
        printf("%d", *x);
    })
}