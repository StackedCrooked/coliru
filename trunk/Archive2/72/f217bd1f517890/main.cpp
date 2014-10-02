#include <set>
#include <cassert>
#include <iostream>
#include <string>
 
int main()
{
  std::set<std::string> set;
  const char * tmp;
  
  tmp = set.insert(std::string("Hello")).first->c_str();
  
  std::cout << (void *)tmp << ": " << tmp << "\n";
  
  tmp = set.insert(std::string("Hello")).first->c_str();
  
  std::cout << (void *)tmp << ": " << tmp << "\n";
 
  return 0;
}