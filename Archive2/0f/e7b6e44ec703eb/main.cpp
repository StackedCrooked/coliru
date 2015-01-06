#include <cstdlib>
#include <cmath>
#include <chrono>
using namespace std::chrono;
#include <cstddef>
#include <vector>
#include <iostream>

int main()
{
  auto start = high_resolution_clock::now();
  const std::size_t N = 1e6;
  
  double sum = 0.;
  std::vector<double> numbers(N);
  for(auto& number : numbers)
    number = std::rand();

  auto end = high_resolution_clock::now();
  std::cout << "initialization: " << (end-start).count() << ".\n";
  
  start = high_resolution_clock::now();
  for(auto number : numbers)
    sum += std::tan(number);

  end = high_resolution_clock::now();
  std::cout << "std::tan: " << (end-start).count() << ".\nSum: " << sum << ".\n";
  sum = 0.;
  
  start = high_resolution_clock::now();
  for(auto number : numbers)
    sum += std::sin(number) /  std::cos(number);

  end = high_resolution_clock::now();
  std::cout << "std::sin/std::cos: " << (end-start).count() << ".\nSum: " << sum << ".\n";
  sum = 0.;
  
  start = high_resolution_clock::now();
  for(auto number : numbers)
    sum += std::tan(number);

  end = high_resolution_clock::now();
  std::cout << "std::tan: " << (end-start).count() << ".\nSum: " << sum << ".\n";
  sum = 0.;
}