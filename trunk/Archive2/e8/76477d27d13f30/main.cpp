#include <iostream>
#include <string>

#define AnsiString std::string

struct A
{
  AnsiString bla;
};

int main()
{
  A a{"blablabla"};
  std::cout << a.bla << '\n';
  a.bla += "bla";
  std::cout << a.bla.substr(2,3) << '\n';
}