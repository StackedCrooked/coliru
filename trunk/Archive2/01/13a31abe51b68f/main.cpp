#include <tuple>

//The standard indecies trick as found on http://loungecpp.wikidot.com/tips-and-tricks:indices
template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};
//end indecies trick


#include <iostream>
#include <array>

//constexpr function generates the std::array of indecies
template<std::size_t...Is>
constexpr std::array<int, sizeof...(Is)> make_indecies(indices<Is...>)
{return std::array<int, sizeof...(Is)>{{Is...}};}

template <int... vars>
struct Compile_Time_Array_Indexes
{
    static constexpr std::array<int,sizeof...(vars)> indexes = make_indecies(build_indices<sizeof...(vars)>());
};
template <int ... vars>
struct Compile_Time_Array :public Compile_Time_Array_Indexes<vars...>
{
};
//the static member must be defined
template <int... vars>
constexpr std::array<int,sizeof...(vars)> Compile_Time_Array_Indexes<vars...>::indexes;
    

int main() {
    Compile_Time_Array<5, 10, 15, 20> data;
    for(const int& i : data.indexes)
        std::cout << i << '\n';
}
