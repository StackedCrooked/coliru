#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>

void
splitinteger(int const n, int const digits, int const split, std::string &a, std::string &b)
{
  std::stringstream ss;
  ss << std::setw(digits) << std::setfill('0') << n;
  a = ss.str().substr(0, split);
  b = ss.str().substr(split);  
}

int main() {
  int i = 9;
  std::string a, b;
  splitinteger(i, 8, 3, a, b);  
  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
}