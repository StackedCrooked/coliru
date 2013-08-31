#include <utility>

template<class P>
struct pair_range_type{
  typename P::first_type begin() const{ return _pair.first; }
  typename P::second_type end() const{ return _pair.second; }
  P _pair;
};

template<class P>
pair_range_type<P> pair_range(P&& p){
  return {std::forward<P>(p)};
}

#include <set>
#include <iostream>

int main() {
    std::multiset<int> s{1,2,2,3,3,3,4,4,4};
    for(auto&& e : pair_range(s.equal_range(3))){
        std::cout << e << " ";
    }
}