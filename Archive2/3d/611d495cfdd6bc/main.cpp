#include <stdio.h> 

int main() 
{ 
  int i, k = 0; 

  for (i = 1; i > 0; i += i) 
    k++; 
  printf("k = %d\n", k); 
  return 0; 
}
