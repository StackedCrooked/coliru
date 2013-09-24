#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  printf("hola %lf\n", sqrt(33));
  int* a = (int*) malloc(sizeof(int));
  *a = 9;
  printf("hola %lf, %d\n", sqrt(33), *a);
  free (a);
  
}
