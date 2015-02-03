#include <iostream>
#include <random>

int main()
{
  std::mt19937 rng;
  rng.seed(0);

  for (int i = 0; i < 10; ++i) {
    std::uniform_int_distribution<> dist(0,5);
    std::cout << dist(rng) << " ";
  }
  std::cout << std::endl;
}