#include <iostream>  // std::cout
#include <string>  // back(), pop_back()                             

int main()
{
  std::string str ("Optimist!");

  std::cout << str.back() << "\n";
  str.pop_back();

  std::cout << str << "\n";
}
