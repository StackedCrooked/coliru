#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int main()
{
  std::string str = "miBaseCompId";
  
  str.erase(std::remove_if(std::begin(str), std::end(str),
                           [](char c){ return std::islower(c); }),
            str.end());
  
  std::cout << str << '\n';
}
