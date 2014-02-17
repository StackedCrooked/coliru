#include <stdio.h>
#include <stdlib.h>
#define N1 5000
#define N2 5000
int main() {
    int imagen[N1][N2];
    int i,j, histo[10];
    
    //Inicialización de "imagen"
    for(i=0; i<N1; i++) {
        for(j=0; j<N2; j++){
            imagen[i][j]=i%10;
        }
    }
    for(i=0; i<10; i++) histo[i] = 0;
    
    #pragma omp parallel private(i,j)
    {        
        int histo_priv[10];
        //Inicializar histotrama privado
        for(i=0; i<10; i++) histo_priv[i] = 0;
        
        #pragma omp for nowait
        for(i=0; i<N1; i++) {
           for(j=0; j<N2; j++) {
               histo_priv[imagen[i][j]]++;
           }
        }      
        #pragma omp critical 
        {
            for(i=0; i<10; i++) histo[i] += histo_priv[i];
        }
    }    
    for(i=0; i<10; i++) printf("%d\n", histo[i]);
    return 0;
}