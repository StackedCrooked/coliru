#include <iostream>

int main()
{
  char i[50][10] = {};
  std::cout << sizeof(i[1]) << '\n';

  char (j[10])[50] = {};
  std::cout << sizeof(j[1]) << '\n';
}
