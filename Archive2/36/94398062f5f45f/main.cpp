#include <cmath>
#include <stdio.h>

int main()
{
  double rate = 0.0021627412080263146;
  double T = 4.0246575342465754;
  double res = exp(-rate * T);
  printf("%0.20f\n", res);
  return 0;
}