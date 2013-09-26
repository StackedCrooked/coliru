#include <iostream>
#include <iterator>
#include <array>
#include <utility>

// these templates will be in <utility> for C++14 
// namespace std

template<unsigned... Indices> 
struct integer_sequence {};

template<unsigned N, unsigned... Indices>
struct make_integer_sequence 
: 
    make_integer_sequence<N-1, N-1, Indices...>
{};

template<unsigned... Indices>
struct make_integer_sequence<0, Indices...> 
: 
    integer_sequence<Indices...>
{};

// } // namespace std

template<class Function, unsigned... Indices>
constexpr auto make_array(Function f, integer_sequence<Indices...>) 
-> std::array<typename std::result_of<Function(unsigned)>::type, sizeof...(Indices)> 
{
    return {{ f(Indices)... }};
}

constexpr double fun(double x) { return x * x; }

int main() 
{
    constexpr auto N = 10;
    constexpr auto a = make_array(fun, make_integer_sequence<N>{});
    
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<double>(std::cout, ", ")); 
}