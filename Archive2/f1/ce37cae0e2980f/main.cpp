#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T typedef struct
#define INT 0
#define FLT 1
T {int type; int refc; } Obj;
T {int type; Obj *data;} List;

void *new(int type, long s, void *data){
    if (type == INT){
        int *d = (int*)data;
        void **ptr = malloc(s * sizeof(int));   
        for (int x=0; x < s; x++){
            ptr[x] = (int*)d[x];
            printf("ORIGINAL-->index: %i, data: %i, addr: %p\n", x, d[x], &d[x]);
        }
        return ptr;
    }
    if (type == FLT){
        float *d = (float*)data;
        void **ptr = malloc(s * sizeof(float));   
        for (int x=0; x < s; x++){
            ptr[x] = (double*)d[x];
            printf("ORIGINAL-->index: %i, data: %f, addr: %p\n", x, d[x], &d[x]);
        }
        return ptr;
    }
//memcpy(ptr, data, sizeof(int) * s);
    printf("\n");

    return 0;
}

int main(){
    int s = 6;
    List *xb = malloc(sizeof(List));
    xb->data = new(INT, s, (int[]){56, 67, 99, 44, 76, 88});
    for (int x=0; x < s; x++){    
        printf("NEW-->index: %i, data: %i, addr: %p\n", x, xb->data[x], &xb->data[x]);
    }
    
    return 0;
}