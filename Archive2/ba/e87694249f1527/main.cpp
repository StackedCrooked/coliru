#include <stdio.h>
#include <stdarg.h>

int my_printf(const char* type, ...)
{
  va_list arg;
  int done;

  va_start(arg, type);
  done = vfprintf(stdout, type, arg);
  va_end(arg);

  return done;
}

int main()
{
    my_printf("%d %d", 1, 2);
}