#include <string>
#include <iostream>
 
int main()
{
  std::string foo("quuuux");
  char bar[7];
  foo.copy(bar, sizeof bar);
  bar[6] = '\0';
  std::cout << bar << '\n';
}