#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>
#include <time.h>
 
int main()
{
  std::string const s("Emplary");
  assert(s.size() == std::strlen(s.c_str()));
  assert(std::equal(s.begin(), s.end(), s.c_str()));
  assert(std::equal(s.c_str(), s.c_str() + s.size(), s.begin()));
  assert(0 == *(s.c_str() + s.size()));
 clock_t start = clock();
  std::cout << s << std::endl;
  clock_t end = clock();
  std::cout << end << std::endl;
}