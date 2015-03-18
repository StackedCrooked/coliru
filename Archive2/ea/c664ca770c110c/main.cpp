#include <iostream>
#include <vector>
#include <algorithm>

namespace n{
class T{
};
}

bool operator==(const n::T&, const n::T&){
  return false;
}

int main(){
  n::T x, y;
  
  std::vector<n::T > z;
  
  std::cout << (x == y);
  
  find(z.begin(), z.end(), x);
}
