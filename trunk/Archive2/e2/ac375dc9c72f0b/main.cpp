#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int main()
{
  std::vector<double> v{1.0, 2.001, 2.002, 1.1, 5.0001, 2.003, 4.0, 5.0005, 5.0};
  
  std::sort(v.begin(), v.end());
  auto last = std::unique(v.begin(), v.end(), [](double l, double r) { return std::abs(l - r) < 0.01; });
  auto first = v.begin();
  
  while(first != last) {
      std::cout << *first++ << ' ';
  }
  std::cout << std::endl;
}
