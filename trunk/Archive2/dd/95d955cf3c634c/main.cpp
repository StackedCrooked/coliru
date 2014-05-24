#include <iostream>

void f(int i)
{
  static int first_i = i;

  std::cout << i*first_i << '\n';
}

int main()
{
  f(3);
  f(4);
}
