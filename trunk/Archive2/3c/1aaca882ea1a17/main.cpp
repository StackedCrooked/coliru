#include <stdio.h>

int main()
{
  printf("(*c >= 0x80) = %d", int(((signed char)81) >= 0x80) );
  return 0;
}
