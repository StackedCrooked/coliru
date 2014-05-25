#include <iostream>     // std::cout
#include <algorithm>    // std::transform
#include <vector>       // std::vector
#include <functional>   // std::plus

int main () {
  std::vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> v2 = {1, 2, 3};

  auto it = v1.begin();
  while (it < v1.end())
    it = std::transform(it, it + v2.size(), v2.begin(), it, std::plus<int>()); // In place sum.

  std::cout << "v1 contains:";
  for (int n : v1)
    std::cout << ' ' << n;
  std::cout << std::endl;

  return 0;
}