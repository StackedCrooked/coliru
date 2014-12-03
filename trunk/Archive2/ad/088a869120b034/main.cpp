#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  char dummy;
  float f;
  if(sscanf(argv[1], "%f%c", &f,&dummy) != 1)
    printf("Input error.\n");
  else
    printf("%f\n", f);
}
