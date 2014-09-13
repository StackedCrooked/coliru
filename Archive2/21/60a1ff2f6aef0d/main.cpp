#include <iostream>
#include <sstream>

int main()
{
  char c = 'A';
  std::stringstream ss("B");

  // I know this is bad mojo; that's why I'm testing it
  ss >> char(c);

  std::cout << c << std::endl;
}