#include <cassert>
#include <string>
 
int main()
{
  std::string s("Exemplar");
  *s.begin() = 'e';
  assert("exemplar" == s);
 
  auto i = s.cbegin();
  assert(s[0] == *i);
}