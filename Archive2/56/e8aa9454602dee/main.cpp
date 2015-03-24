#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
 
int main(int argc, char **argv, char **aenv)
{
    while (*aenv)
      printf("'%s'\n", *aenv), aenv++;
}
