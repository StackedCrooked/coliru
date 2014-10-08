#include <iostream>
#include <functional>
#include <numeric>

int main () {
  int val[] = {1,2,3,5,9,11,12};
  int result[7];

  std::adjacent_difference (val, val+7, result);
  for(auto i : val) std::cout << i << " ";
  std::cout << std::endl;
}