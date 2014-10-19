#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>
 
int main()
{
  std::string const s("Emplary");
  assert(s.size() == std::strlen(s.data()));
  assert(std::equal(s.begin(), s.end(), s.data()));
  assert(std::equal(s.data(), s.data() + s.size(), s.begin()));
  assert(0 == *(s.data() + s.size()));
  
  const char *sc = s.c_str();
  printf("%s\n", sc);
  printf("%s\n", s.data());
  std::cout << s;
}