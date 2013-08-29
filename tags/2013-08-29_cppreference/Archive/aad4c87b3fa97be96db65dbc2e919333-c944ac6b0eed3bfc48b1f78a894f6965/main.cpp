#include <unistd.h>
#include <stdio.h>

#define N 5
#define READ 0
#define WRITE 1

int f(int n) { return 2*n; }

int main(){
    int cev[N-1][2];
    
    for(int i=0; i<N-1; i++) pipe(cev[i]);
    
    for(int i=0; i<N; i++){
        if(fork() == 0){ // child
            int a = 1;
            if(i>0) {
                read(cev[i-1][READ],&a,sizeof(int));
                a = f(a);  // calculate next element
            }
            printf("%d\n",a);
            fflush(stdout);                        
            if(i!=N-1)
              write(cev[i][WRITE],&a,sizeof(int));
    
            return 0;
        }
    }
}
