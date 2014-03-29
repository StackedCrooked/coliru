#include <iostream>

void do_one()
{
  static int x;
  int y;
  y = ++x;
}

void do_two()
{
  int x;
  std::cout << x;
}

int main()
{
  do_one();
  do_two();
  return 0;
}