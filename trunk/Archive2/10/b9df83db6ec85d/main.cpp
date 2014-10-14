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
template <typename... TS, std::size_t... Is> 
void toTpl(const JVal& mV, std::tuple<TS...>& mX, std::index_sequence<Is...>) 
{ 
    using Tuple = std::tuple<TS...>;
    int dummy[] = { 0, ((void)(std::get<Is>(mX) = mV[Is].as<std::tuple_element_t<Is, Tuple>>()), 0)... };
    (void)dummy;
}

template <typename... TS> 
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
