#include <iostream>
#include <vector>
#include <iterator>

int main() 
{
  std::vector<int> vec{0,1,2,3,4,5,6};
  
  for(auto it = vec.begin(); 
      std::distance(it, vec.end()) >= 2;
      std::advance(it, 2)) {
    std::iter_swap(it, std::next(it, 1));        
  }
  
  for(auto const& v : vec) {
      std::cout << v << ' ';
  }
  std::cout << '\n';
}
