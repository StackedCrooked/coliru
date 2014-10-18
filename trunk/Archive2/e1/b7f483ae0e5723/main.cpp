#include <iostream>
#include <vector>

template <typename T>
std::vector<T>& operator+=(std::vector<T>& lhs, std::vector<T> const &rhs)
{
    lhs.insert(lhs.end(), rhs.begin(), rhs.end());
    return lhs;
}

int main() {
  std::vector<int> v {1, 2, 3, 4, 5};
  v += v;
  for(auto i : v) std::cout << i << " ";
  std::cout << std::endl;
}