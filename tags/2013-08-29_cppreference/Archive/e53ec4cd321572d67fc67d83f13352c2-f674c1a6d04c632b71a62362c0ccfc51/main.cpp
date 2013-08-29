#include <cstdio>

#define LENGTH(X) \
  int length = sizeof(X)/sizeof(char) - 1; \
  printf("%s => %d", X, length);

int main()
{
  LENGTH("123456789"); 
}