#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
        int cod;
}car;

int main(int argc, char *argv[])
{
  int i;
  car store[10];
  srand(time(NULL));
  for (i=0;i<10;i++){
      store[i].cod=rand();
  }
  system("PAUSE");  
  return 0;
}