#include<stdio.h>

//                   a         3        i          i
void reduction(float a[][8], int size, int pivot, int col) {
   int i, j;
   float factor;
   factor = a[pivot][col];

   for (i = 0; i < 2 * size; i++) {
      a[pivot][i] /= factor;
   }

   for (i = 0; i < size; i++) {
      if (i != pivot) {
         factor = a[i][col];
         for (j = 0; j < 2 * size; j++) {
            a[i][j] = a[i][j] - a[pivot][j] * factor;
         }
      }
   }
}


void InverseMatrix(float matrix[][8],int size){
    int i;
       for (i = 0; i < size; i++){
      reduction(matrix, size, i, i);
   }
}
void PrintMatrix(float matrix[][8],int size){
   
   int i,j;
   for (i = 0; i < size; i++) {
      printf("\n");
      for (j = 0; j < 2*size; j++) {
         printf("%8.3f", matrix[i][j]);
      }
   }
}


int main() {
    int size =4;
    float matrix[4][8] = { { 1.2,-0.4,0, 0,1,0, 0 ,0 }, {-0.5,1.4,-0.3,0 ,0,1,0,0 }, { 0,-0.4,1.1,-0.6,0,0,1,0 }, {0,0,-0.5,1.3,0,0,0,1} };
   
   InverseMatrix(matrix, size);
  
   printf("\nInvers Matrix");
    PrintMatrix(matrix,size);

   return 0;
}