#include <iostream>
#include <limits>

int main() {
  double r = -0.0f;
   
  auto EPSILON = std::numeric_limits<double>::epsilon();
  if (r < 0.0 - EPSILON) {
    std::cout<< "Negative zero was less";
  } else {
    std::cout << "Negative zero Not less";
  }
   
  return 0;
}