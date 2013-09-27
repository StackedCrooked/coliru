#include <iostream>
#include <vector>
#include <numeric>

static constexpr struct {
    template<class F>
    constexpr auto operator->*(F&& f){ return f(); }
} call;

#define let call ->* [&, 
  
#define in ] () mutable
  
std::vector<int> g(){ return {1,2,3,4,5}; }

int main(){
    let v = g(), a = 10
    in { std::cout << std::accumulate(v.begin(), v.end(), a) << "\n"; };
}