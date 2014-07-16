#include <iostream>

int main()
{
  int input;

  std::cout << "Enter integer: ";
  std::cin >> input;
  std::cout << "\nYou entered: " << input << "\n\n" ;

  std::cout << "Enter five integers: " ;
  std::cin >> input ; std::cout << "\nYou entered: " << input << ' ' ;
  std::cin >> input ; std::cout << input << ' ' ;
  std::cin >> input ; std::cout << input << ' ' ;
  std::cin >> input ; std::cout << input << ' ' ;
  std::cin >> input ; std::cout << input << '\n' ;
}
