#include <stdlib.h>
#include <stdio.h>
 
_Noreturn void stop_now() {
  abort();
}
 
int main(void)
{
  printf("Preparing to stop...\n");
 
  stop_now();
 
  printf("This code is never executed.\n");
 
  return EXIT_SUCCESS;
 
}