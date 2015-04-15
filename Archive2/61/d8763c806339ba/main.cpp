#include <chrono>
#include <random>
#include <iostream>

int main()
{
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(1,11111);
  
  std::cout<<distribution(generator)<<std::endl;
}
