#include <stdarg.h>
#include <stdio.h>

struct Dummy{}; // <-- This corrupts last argument

//struct Dummy {char x;}; // <-- This works fine.

void fun(Dummy, const char* msg, ...)
{
  va_list args;
  va_start(args, msg);
  vprintf(msg, args);  
  va_end(args);
}

int main()
{
  fun(Dummy(), "%d %d %d %d %d %d", 1,2,3,4,5,6);
  return 0;
}
