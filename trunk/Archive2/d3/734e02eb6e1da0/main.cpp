// main.cpp
#include <random>

int main()
{
  std::seed_seq seed1{1337, 42};
  std::seed_seq seed2(seed1);
  std::seed_seq seed3 = seed2;
}
