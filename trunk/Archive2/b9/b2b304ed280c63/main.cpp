#include <iostream>
#include <tuple>
#include <type_traits>
#include <string>

template <size_t i>
using Index = std::integral_constant<size_t, i>;

template <class... Types>
struct Tuple : std::tuple<Types...>
{
    using std::tuple<Types...>::tuple;
    
    template <size_t i>
    auto operator [] (const Index<i>&) -> decltype(std::get<i>(*this))
    {
        return std::get<i>(*this);
    }
    
    template <size_t i>
    auto operator [] (const Index<i>&) const -> decltype(std::get<i>(*this))
    {
        return std::get<i>(*this);
    }
};

template <size_t N, char... Digits>
struct Number_ : std::integral_constant<size_t, N> {};

template <size_t N, char Digit, char... Digits>
struct Number_<N, Digit, Digits...> :
    std::integral_constant<size_t, Number_<N * 10 + (Digit - '0'), Digits...>::value>
{
    static_assert(('0' <= Digit) && (Digit <= '9'), "Invalid digit in index string");
};

template <char... Digits>
struct Number : Number_<0, Digits...> {};

template <char... Digits>
constexpr Index<Number<Digits...>::value> operator "" _i() noexcept
{
    return {};
}

int main() {
    int i = 42;
    double f = 3.14;
    std::string s = "Hello, world!";
    Tuple<int, double, std::string> t(i, f, s);
    
    std::cout << t[0_i] << std::endl;
    std::cout << t[1_i] << std::endl;
    std::cout << t[2_i] << std::endl;
}