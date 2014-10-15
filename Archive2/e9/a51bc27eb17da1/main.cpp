#include <iostream>
#include <algorithm>
#include <random>

int main() {
  int n[] = {1, 3, 5, 7, 9};
  std::size_t n_size = sizeof(n) / sizeof(int);

  std::default_random_engine generator;  
  for(std::size_t i(0), sz(n_size); i < sz; ++i) {
    std::cout << "before removal:" << std::endl;
    std::cout << "  ";
    for(std::size_t j(0); j < n_size; ++j) std::cout << n[j] << " ";
    std::cout << std::endl;
    --n_size;
    std::uniform_int_distribution<int> distribution(0, n_size);
    std::size_t idx = distribution(generator);
    std::cout << "  Removing index: " << idx << std::endl;
    std::swap(n[idx], n[n_size]);
    std::sort(std::begin(n), std::begin(n) + n_size); // use your sorting here
    std::cout << "after removal:" << std::endl;
    std::cout << "  ";
    for(std::size_t j(0); j < n_size; ++j) std::cout << n[j] << " ";
    std::cout << "\n" << std::endl; 
  } 
}