#include <stdio.h>
#include <stdlib.h>
#define N1 100
#define N2 100
int main() {
    int img[N1][N2];
    int i, histogram[10];
    for(i=0; i<N1*N2; i++) img[i/N2][i%N2]=rand()%10;
    for(i=0; i<10; i++) histogram[i] = 0;
    #pragma omp parallel
    {
        int i, j, histogram_private[10];
        for(i=0; i<10; i++) histogram_private[i] = 0;
        #pragma omp for nowait
        for(i=0; i<N1; i++) {
           for(j=0; j<N2; j++) {    
               histogram_private[img[i][j]]++;
           }
        }      
        #pragma omp critical 
        {
            for(i=0; i<10; i++) histogram[i] += histogram_private[i];
        }
    }
    for(i=0; i<10; i++) printf("%d\n", histogram[i]);
    return 0;
}