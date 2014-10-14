#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

namespace std
{
    template <std::size_t N, typename T>
    using tuple_element_t = typename std::tuple_element<N, T>::type;
}

struct HasAs
{
    int i;
    HasAs(int i) : i(i) {}
    template <typename T> T as() { return i; }
};

struct JVal
{
    HasAs operator[](int i) const { std::cout << "at(" << i << ")" << std::endl; return {i}; }
};

// START
template <typename... Ts, std::size_t... Is> 
std::tuple<Ts...> toTpl(const JVal& mV, std::index_sequence<Is...>) 
{ 
    using Tuple = std::tuple<Ts...>;
    return Tuple{ mV[Is].as<std::tuple_element_t<Is, Tuple>>()... };
}

template<typename... Ts> 
std::tuple<Ts...> toTpl(const JVal& mV)
{
    return toTpl<Ts...>(mV, std::make_index_sequence<sizeof...(Ts)>{});
}
// END

int main()
{
    JVal mV;
    auto t = toTpl<int, float, double>(mV);
    
    std::cout << std::get<0>(t) << std::endl;
    std::cout << std::get<1>(t) << std::endl;
    std::cout << std::get<2>(t) << std::endl;
}
