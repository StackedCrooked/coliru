#include <iostream>

volatile double epsilon = 1;
volatile float epsilon_f = 1;
int main() {
  while(1 + epsilon > 1)
    epsilon = epsilon / 2;
  epsilon = 2*epsilon;

  std::cout << epsilon << std::endl;

  while(1 + epsilon_f > 1)
    epsilon_f = epsilon_f / 2;
  epsilon_f = 2*epsilon_f;

  std::cout << epsilon_f << std::endl;

  return 1;
}
