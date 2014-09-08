#include <iostream>
#include <string>

int main()
{
  for (int ii = 0; ii < 1; ++ii)
  {
    const std::string& str = str; // !!
    std::cout << str << std::endl;
  }
}