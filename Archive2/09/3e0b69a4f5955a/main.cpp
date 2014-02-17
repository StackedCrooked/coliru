#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N1 5000
#define N2 5000
int main() {
    int i,j, histo[10];

    //Declaro y reservo memoria para "imagen"
    int** imagen;    
    imagen = (int**)malloc(N1* sizeof(int*));
    for (i = 0; i < N1; i++) {
        imagen[i] = (int*)malloc(N2 * sizeof(int));
    }
    
    //Inicialización de imagen
    for(i=0; i<N1; i++){
        for(j=0; j<N2; j++){
            imagen[i][j]=i%10;  
        }    
    }
    
    //Inicialización del histograma
    for(i=0; i<10; i++) histo[i] = 0;
    
    #pragma omp parallel private(i,j)
    {
        int histo_priv[10];
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