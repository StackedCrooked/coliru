#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
  std::vector<int> v{1, 2, 8, 3, 5, 4, 5, 6, 7, 7, 9, 9, 19, 19};
  v.erase(std::unique(v.begin(), v.end()), v.end());
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, v.size() - 1);
  
  std::cout << "Random number from vector: " << v[distribution(generator)] << std::endl;
  
  return 0;
}