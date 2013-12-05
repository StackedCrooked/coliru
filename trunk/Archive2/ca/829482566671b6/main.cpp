#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

_Bool is_palindrome(const char* s)
{
  const size_t len = strlen(s);
  size_t i=0;
  while(i<len/2-1)
  {
    if(s[i] != s[len-i-1])
      return false;

    ++i;
  }
  return true;
}

int main()
{
  const char* s1 = "palindrome";
  const char* s2 = "palindromemordnilap";
  
  if(is_palindrome(s1))
    printf("uhoh");
  if(is_palindrome(s2))
    printf("yay!");
}
