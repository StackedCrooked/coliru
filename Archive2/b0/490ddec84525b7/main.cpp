#include <iostream>

int main() {
  double epsilon = 1;
  volatile double sum = 1;
  while(sum = 1.0 + epsilon/2, sum > 1)
    epsilon = epsilon / 2;

  std::cout << epsilon << std::endl;

  float epsilon_f = 1;
  volatile float sum_f = 1.0f;
  while(sum_f = 1.0f + epsilon_f/2.0f, sum_f > 1)
    epsilon_f = epsilon_f / 2;

  std::cout << epsilon_f << std::endl;

  return 1;
}
