#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    
} Int32;

int main(){
    
    int x = 88;
    int y = 44;
    int z = 48;
    
    Int32 ptr;
    
    ptr.data = &x;
    printf("data: %i | address: %p | %p\n", *ptr.data, &ptr.data, &x);
    ptr.data = &y;
    printf("data: %i | address: %p | %p\n", *ptr.data, &ptr.data, &y);
    ptr.data = &z;
    printf("data: %i | address: %p | %p\n", *ptr.data, &ptr.data, &z);
    
    return 0;
}