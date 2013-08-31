#include <iostream>

int f(int i)
{
  static bool bla = true;
  bla  = !bla;
  return bla ? i : -i;
}
  
int main()
{
  std::cout << f(f(42));
}