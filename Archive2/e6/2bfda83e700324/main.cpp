#include <cmath>
#include "assert.h"
#include <iostream>

int main () {
  int n = 8;
  unsigned int i =
    static_cast<unsigned int>(std::log(static_cast<double>(n)) /
                              std::log(static_cast<double>(2)));
  double d =
    std::log(static_cast<double>(n)) / std::log(static_cast<double>(2));
  unsigned int j = static_cast<unsigned int> (d);
  std::cout << i << ' ' << j << std::endl;
  assert (i == j);
}