#include <iostream>
#include <string>
 
int main()
{
  {
    std::string const c("Exemplar");
    for (unsigned i = 7;i != 0; i/=2)
        std::cout << c[i];
  }
    std::cout << '\n';
  {
    std::string s("My name is Jesse ");
    s[s.size()-1] = 'y';
    std::cout << s;
  }
}