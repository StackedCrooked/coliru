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

template <size_t i>
constexpr Index<i> I{};

int main() {
    int i = 42;
    double f = 3.14;
    std::string s = "Hello, world!";
    Tuple<int, double, std::string> t(i, f, s);
    
    std::cout << t[I<0>] << std::endl;
    std::cout << t[I<1>] << std::endl;
    std::cout << t[I<2>] << std::endl;
}