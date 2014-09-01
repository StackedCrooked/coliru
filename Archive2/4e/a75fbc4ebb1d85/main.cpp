// regex_search example
#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string s ("<?php $foo = 'bar'; /*but this is a php file */ $baz = \"baz\";");
  std::smatch m;
  std::regex e ("[$][a-zA-Z_\\x7f-\\xff][a-zA-Z0-9_\\x7f-\\xff]*");   // php variables
  std::cout << "The following matches and submatches were found:" << std::endl;

  while (std::regex_search (s,m,e)) {
    for (auto x:m) std::cout << x << " ";
    std::cout << std::endl;
    s = m.suffix().str();
  }

  return 0;
}