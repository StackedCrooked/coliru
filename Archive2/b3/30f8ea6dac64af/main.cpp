#include <stdio.h> 

   int main(void)
{
  int x; long long int s=0; 

  for(x=1; x <= 14 ; x++) 
  {
    s=(s+2)*x; 
   if (s<=9000000)
  printf("%lld ", s);
}
  return 0;
} 