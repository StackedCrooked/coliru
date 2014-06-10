#include <iostream>

int main () {
  int x;

  while (std::cin >> x)
    ;

  std::cout << "waiting: ";
  std::cin.clear ();
  std::cin >> x;
  
  std::cout << "end";
}