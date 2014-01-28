#include <stdio.h>
#include <stdarg.h>
 
/* print all non-negative args one at a time;
   all args are assumed to be of int type */
void printargs(int arg1, ...)
{
  va_list ap;
  int i;
 
  va_start(ap, arg1); 
  for (i = arg1; i >= 0; i = va_arg(ap, int))
    printf("%d ", i);
  va_end(ap);
  putchar('\n');
}
 
int main(void)
{
   printargs(5, 2, 14, 84, 97, 15, 24, 48, -1);
   printargs(84, 51, -1);
   printargs(-1);
   printargs(1, -1);
   return 0;
}