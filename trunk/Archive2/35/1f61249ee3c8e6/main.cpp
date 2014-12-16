#include <stdio.h>
void foo() {
    float v1[3] = {1,2,3};
    float v2[3] = {};
    float matrix[3][3] = {{2,3,4},{3,4,5},{4,5,6}};
    int tam = 3;
    #pragma omp parallel
    {
        int i,j;
        #pragma omp for
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
              v2[i] += matrix[i][j] * v1[j];
            }
        }
    }
    for(int i=0; i<3; i++) printf("%f\n", v2[i]);
}

void foo2() {
    const int tam = 3;
    float v1[3] = {1,2,3};
    float v2[3] = {};
    float matrix[3][3] = {{2,3,4},{3,4,5},{4,5,6}};
    
    #pragma omp parallel
    {
        float v2_private[tam] = {};
        int i,j;
        for (i = 0; i < tam; i++) {
            #pragma omp for
            for (j = 0; j < tam; j++) {
                v2_private[i] += matrix[i][j] * v1[j];
            }
        }
        #pragma omp critical
        {
            for(i=0; i<tam; i++) v2[i] += v2_private[i];
        }
    }
    for(int i=0; i<3; i++) printf("%f\n", v2[i]);
}

int main() {
    foo();
    foo2();
}