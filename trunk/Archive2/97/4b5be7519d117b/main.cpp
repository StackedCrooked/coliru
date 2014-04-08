#include <iostream>
#include <limits>
#include <cmath>

int main()
{
  double l = std::numeric_limits<double>::lowest();
  double next = std::nextafter(l, 0.0);
  std::cout << next - l << '\n';
}