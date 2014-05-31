#include <tuple>

//indecies trick
template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};
 
template <typename Tuple>
using IndicesFor = build_indices<std::tuple_size<Tuple>::value>;
//end indecies trick




template<class...Ts, std::size_t...Is>
bool all_equal_w_indecies(indices<Is...>, const Ts&...ts) 
{
    auto tied = std::tie(ts...);
    bool eq[] = {std::get<Is>(tied)==std::get<Is+1>(tied)...};
    
    for(int i=0; i<sizeof...(Is); ++i)
        if (eq[i] == false)
            return false;
            
    return true;
}
template<class...Ts>
bool all_equal(const Ts&...ts) 
{return all_equal_w_indecies(build_indices<sizeof...(Ts)-1>(), ts...);}





#include <iostream>
#include <string>
int main() {
    std::cout << all_equal(std::string("HI"), "HI");    
}