#include <iostream>
#include <string>
#include <cstring>
int main ()
{
  constexpr const char* literal = "123\0 456";
  constexpr const std::size_t real_length = 8;
  std::cout << literal << '\n';
  std::string s;
  s.resize(8);
  std::copy(literal, literal+real_length, &s[0]);
  std::cout << s << '\n';
}