#include <stdio.h>

const char* str = myfunc;

int main(void)
{
   const char myfunc[] = "main";
   printf("%s", str);
   return 0;
}