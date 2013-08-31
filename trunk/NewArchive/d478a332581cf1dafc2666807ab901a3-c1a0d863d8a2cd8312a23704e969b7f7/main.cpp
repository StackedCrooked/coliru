#include <stdio.h>
#include <math.h>

int main()
{
  double e = 36858.767828375385;
  double c = 2;
  double d= 67.877433500000009;

  e = sqrt(e/(c*(c-1)))/d;
  printf("e=%f\n", e);
  
  e = sqrt(e/(c*(c-1.)))/d;
  printf("e=%f\n", e);
}
