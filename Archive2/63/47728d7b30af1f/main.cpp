#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  std::vector<int> first {5,10,15,20,25};
  std::vector<int> second {50,40,30,20,10};
  std::vector<int> v(10);
  std::sort (first.begin(), first.end());
  std::sort (second.begin(), second.end());
  std::merge (first.begin(), first.end(), second.begin(), second.end(), v.begin());
  for(auto i : v) std::cout << i << " ";
  std::cout << std::endl;
}