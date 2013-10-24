// example on extraction
#include <iostream>     // std::cin, std::cout, std::hex

int main () {
  int n;

  std::cout << "Enter a number: ";
  std::cin >> n;
  std::cout << "You have entered: " << n << '\n';

  std::cout << "Enter a hexadecimal number: ";
  std::cin >> std::hex >> n;         // manipulator
  std::cout << "Its decimal equivalent is: " << n << '\n';

  return 0;
}