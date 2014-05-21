#include <cassert>
#include <string>
 
int main()
{
  {
    std::string s("Exemplary");
    char& f = s.front();
    f = 'e';
    assert("exemplary" == s);
  }
 
  {
    std::string const c("Exemplary");
    char const& f = c.front();
    assert('E' == f);
  }
}