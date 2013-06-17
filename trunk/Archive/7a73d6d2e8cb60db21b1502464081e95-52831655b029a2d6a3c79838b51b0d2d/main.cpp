#include <vector>
#include <tuple>
#include <algorithm>

template<class... Ts>
std::vector<std::tuple<Ts...>> zip(std::vector<Ts> const&... vs){
    auto lo = std::min({vs.size()...});
    std::vector<std::tuple<Ts...>> v;
    v.reserve(lo);
    for(unsigned i = 0; i < lo; ++i)
        v.push_back(std::make_tuple(vs[i]...));
    return v;
}

#include <iostream>

int main(){
    std::vector<int> a{1,3,5}, b{2,4,6}, c{3,5,7};
    for(auto&& t : zip(a, b, c)){
        std::cout << std::get<0>(t) << ":" << std::get<1>(t) << ":" << std::get<2>(t) << "\n";
    }
}