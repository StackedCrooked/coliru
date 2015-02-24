                                                                                                        /* va_arg example */
#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

int FindMax (int n, ...)
{
  int i,val,largest;
  va_list vl;
  va_start(vl,n);
  largest=va_arg(vl,int);
  for (i=1;i<n;i++)
    {
      val=va_arg(vl,int);
      printf("%d ", val);
      largest=(largest>val)?largest:val;
    }
  va_end(vl);
  return largest;
}

int main ()
{
  int m;
  m= FindMax(7,702,422,631,834,892,104,772);
  printf ("\nThe largest value is: %d\n",m);
  return 0;
}
