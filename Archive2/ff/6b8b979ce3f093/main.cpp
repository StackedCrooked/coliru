#include <tuple>
#include <iostream>
#include <string>
 
template <int N, typename T, typename U>
static auto constexpr get(std::pair<T, U> const& pair)
    -> typename std::tuple_element<N, decltype(pair)>::type
{
    return N == 0 ? pair.first : pair.second;
}
 
int main()
{
    auto var = std::make_pair(1, std::string{"one"});
 
    std::cout << get<0>(var) << " = " << get<1>(var);
}