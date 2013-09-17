#include <map>
#include <iostream>


void multiplyMatrices(int matrixA[5][5], int matrixB[5][5],int matrixC[5][5]){
     int i, n, j;

         printf("\n");
 printf("Matrix A x Matrix B = \n");
 for (i = 0; i<5; i++){
    for (n = 0; n<5; n++){
        for (j = 0; j<5; j++){
            matrixC[i][n] += matrixA[i][j]*matrixB[j][n];
            std::cout << matrixC[i][n] << " ";
      }
      std::cout << std::endl;
    }
  }
}

int main() {
    int a[5][5];
    int b[5][5];
    int c[5][5];
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            a[i][j] = i+j;
            b[i][j] = j-i;
            c[i][j] = i*j;
        }
    }
    multiplyMatrices(a,b,c);
    return 0;
}