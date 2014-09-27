#include <iostream>
#include <algorithm>
#include <iterator>

template<typename T>
std::ostream& operator<<(std::ostream &out, std::vector<T> const &v) {
  std::copy(v.cbegin(), v.cend(), std::ostream_iterator<T>(out, " "));
  out << std::endl;
  return out;
}

int main() {
  std::vector<int> iv {1, 2, 3, 4, 5};
  std::vector<double> dv {1.1, 1.2, 1.3, 1.4, 1.5};
  std::cout << iv << std::endl;
  std::cout << dv << std::endl;
}