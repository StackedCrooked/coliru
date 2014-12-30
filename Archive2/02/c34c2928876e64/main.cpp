#include <iostream>
#include <string>
#include <regex>

int main ()
{
  // the following two lines are edited; the remainder are directly from the reference.
  std::string s ("aaa,bbb.ccc,ddd-eee;");
  std::regex e ("([.,;-]|[^.,;-]+)");   // matches delimiters or consecutive non-delimiters

  std::regex_iterator<std::string::iterator> rit ( s.begin(), s.end(), e );
  std::regex_iterator<std::string::iterator> rend;

  while (rit!=rend) {
    std::cout << rit->str() << std::endl;
    ++rit;
  }

  return 0;
}