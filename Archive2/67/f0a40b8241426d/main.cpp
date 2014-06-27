// regex_search example
#include <iostream>
#include <string>
#include <tr1/regex>

namespace std
{
    using namespace std::tr1;
}

int main ()
{
  std::string s ("this subject has a submarine as a subsequence");
  std::smatch m;
  std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  std::cout << "Target sequence: " << s << std::endl;
  std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
  std::cout << "The following matches and submatches were found:" << std::endl;

  return 0;
}