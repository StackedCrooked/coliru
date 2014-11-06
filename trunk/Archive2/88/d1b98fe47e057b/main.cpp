#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

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
auto as_tuple(const JVal& mV, std::index_sequence<Is...>) 
{ 
    return std::tuple<Ts...>{ mV[Is].as<Ts>()... };
}

template<typename... Ts> 
auto as_tuple(const JVal& mV)
{
    return as_tuple<Ts...>(mV, std::index_sequence_for<Ts...>{});
}
// END

int main()
{
    JVal mV;
    auto t = as_tuple<int, float, double>(mV);
    
    std::cout << std::get<0>(t) << std::endl;
    std::cout << std::get<1>(t) << std::endl;
    std::cout << std::get<2>(t) << std::endl;
}
