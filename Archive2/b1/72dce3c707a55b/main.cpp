#include <stdlib.h>
#include <stdio.h>

int main() {
    int matrix_size = 3;
    double vector[3] = {1,2,3};
    double results[3] = {};
    double matrix[3][3] = {{2,3,4},{3,4,5},{4,5,6}};
    
    #pragma omp parallel num_threads(4)
    {
        int y,i;
        double* results_private = (double*)calloc(matrix_size, sizeof(double));
        for(y = 0; y < matrix_size ; y++) {
            #pragma omp for
            for(i = 0; i < matrix_size; i++) {
                results_private[y] += vector[i]*matrix[i][y];   
            }
        }
        #pragma omp critical
        {
            for(y=0; y<matrix_size; y++) results[y] += results_private[y];
        }
        free(results_private);
    }
    for(int i=0; i<matrix_size; i++) printf("%f\n", results[i]);
}