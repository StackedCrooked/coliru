#include <stdio.h>

int main()
{
  int i=0, j=0, erg;
  erg = i++ && j++;
  printf("%d %d %d", i, j, erg);
  return 0;
}
