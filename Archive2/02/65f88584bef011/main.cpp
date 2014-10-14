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
template <std::size_t N, typename... TS>
void op(const JVal& mV, std::tuple<TS...>& mX)
{
    using Tuple = std::tuple<TS...>;
    std::get<N>(mX) = mV[N].as<std::tuple_element_t<N, Tuple>>();
}

template <typename... TS, std::size_t... Is>
void toTpl(const JVal& mV, std::tuple<TS...>& mX, std::index_sequence<Is...>) 
{ 
    auto x = { 0, ((void)op<Is>(mV, mX), 0)... };
    (void)x;
}

template<int TI = 0, typename... TS> 
void toTpl(const JVal& mV, std::tuple<TS...>& mX)
{
    toTpl(mV, mX, std::make_index_sequence<sizeof...(TS)>{});
}
// END

int main()
{
    std::tuple<int, float, double> t;
    JVal mV;
    toTpl(mV, t);
    
    std::cout << std::get<0>(t) << std::endl;
    std::cout << std::get<1>(t) << std::endl;
    std::cout << std::get<2>(t) << std::endl;
}
