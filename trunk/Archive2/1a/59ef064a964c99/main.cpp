#include <iostream>
int main ()
 {
  std::cout << "cin.putback() demonstration: Please, enter a number ";
  char c;
  int n;
  std::cin >> c;
  std::cin.putback (c);
  std::cin >> n;
  std::cout << "You entered a putback number n: " << n << '\n';
  std::cout << "You entered a number c: " << int(c) << " (" << int('0') << '+' << (c - '0') << ") \n";
  return 0;
}