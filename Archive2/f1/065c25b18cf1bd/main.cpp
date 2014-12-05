#include <cstdio>   //corrected


int x=1, y=3, z=7;

void duplicate (int a, int b, int c)
{
  a=a*2;
  b=b*2;
  c=c*2;
}

int main ()
{
  
  duplicate (x, y, z);
  printf("The answer is %i and %i and %i",x,y,z);
  
  return 0;
}