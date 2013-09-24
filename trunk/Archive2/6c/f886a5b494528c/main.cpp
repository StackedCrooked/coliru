#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(0));
  int* a = (int*) malloc(sizeof(int));
  *a = 19;
  
  int* b =(int*) malloc(sizeof(int));;
  memcpy(b, a, sizeof(int));
  *b=7;
  printf("hola %f, %d, %d, %d\n", sqrt(33), *a, rand()%24, *b);  
  free (a);
  
}
