#include <iostream>
#include <cstring>
 
int main()
{
  const char *str = "Try not. Do, or do not. There is no try.";
  char target = 'T';
  const char *result = str;
 
  while ((result = std::strchr(result, target)) != NULL) {
    std::cout << "Found '" << target
              << "' starting at '" << result << "'\n";
 
    // Increment result, otherwise we'll find target at the same location
    ++result;
  }
}