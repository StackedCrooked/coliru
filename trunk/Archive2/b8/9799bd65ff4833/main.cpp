#include <array>    // array
#include <cstddef>	// size_t
#include <iostream> // cout
#include <utility>	// index_sequence, make_index_sequence

namespace detail {

template<class Function, std::size_t... Indices>
constexpr auto make_array_helper(Function f, std::index_sequence<Indices...>)
-> std::array<decltype(f(std::size_t{})), sizeof...(Indices)>
{
        return {{ f(Indices)... }};
}

}       // namespace detail

template<std::size_t N, class Function>
constexpr auto make_array(Function f)
{
        return detail::make_array_helper(f, std::make_index_sequence<N>{});
}

constexpr auto square_plus_one(std::size_t x)
{
    return (x + 1) * (x + 1);    
}

int main()
{
    auto constexpr squares = make_array<5>(square_plus_one);
    
    for (x : squares)
        std::cout << x << ",";
}
