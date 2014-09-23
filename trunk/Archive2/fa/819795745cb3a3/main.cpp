#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
  std::size_t i(0);
  std::vector<int> v1 {1, 2, 3, 4, 5};
  std::vector<int> v2 {5, 4, 3, 2, 1};
  std::vector<int> v3(5);
  std::transform(v1.begin(), v1.end(), v3.begin(), [&](int x) mutable { int res = x + v2[i];
                                                                        ++i;
                                                                        return res;
                                                                      });
  for(auto i : v3) std::cout << i << " ";
  std::cout << std::endl;
}