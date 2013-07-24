#include <iostream>
#include <vector>
#include <numeric>

#define let \
  if(bool _done_ = false){} else \
  for(auto&&
  
#define in \
  ; !_done_; _done_ = true)
  
std::vector<int> g(){ return {1,2,3,4,5}; }

int main(){
    let v = g() in
        std::cout << std::accumulate(v.begin(), v.end()) << "\n";
}