#include <stdio.h> 
#include <malloc.h> 
#define sizeMalloc(p) (*(((unsigned int *)p)-1) & ~(0x01|0x02)) 

int main(void) {    
    int i=0;    
    for(i=0; i<30; i++) {
        void* p = malloc(i);       
        printf("malloc %d-%d-%d bytes!\n", i,sizeof(p), sizeMalloc(p));       
        free(p);    
        }    
    return 0; 
}