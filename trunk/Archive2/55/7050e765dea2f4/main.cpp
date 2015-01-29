#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <type_traits>
#include <tuple>

using namespace std;

template<size_t... Ints>
struct range 
{
    using type = range<Ints...>;   
};

template<size_t N, size_t... Ints>
struct range<N, Ints...>
{
    using type = typename range<N-1, N, Ints...>::type;    
};

template<size_t ...N>
struct range<0, N...>
{
    using type = range<0, N...>;
};
template<size_t N>
struct count_to
{
    using type = typename range<N-1, N>::type;
};
template<>
struct count_to<-1>
{
    using type = range<>;
};
template<>
struct count_to<0>
{
    using type = range<0>;   
};

template<typename T>
struct compare 
{
    static constexpr size_t value = -1;
};

template<typename FuncT, typename... ArgsTF>
struct compare <FuncT(*)(ArgsTF...)>
{    
    static constexpr size_t value = sizeof...(ArgsTF);
};

template<typename FuncT, typename... ArgsTF>
struct compare <FuncT(&)(ArgsTF...)>
{    
    static constexpr size_t value = sizeof...(ArgsTF);
};

template<typename FuncT, typename ParamsT>
struct explode_impl
{    
    template<size_t... Indexes>
    static auto apply(FuncT func, ParamsT& params, range<Indexes...>) -> decltype(func(get<Indexes>(params)...))
    {        
        //
        return func(get<Indexes>(params)...);   
    }
};

template<typename FuncT, typename ...ArgsT>
struct returnType 
{   
    static_assert(compare<FuncT>::value == sizeof...(ArgsT), "Wrong number of arguments");    
    using type = typename result_of<FuncT(ArgsT...)>::type;
};

template<typename FuncT, typename... ArgsT>
static auto explode(FuncT func, tuple<ArgsT...>& params) -> typename returnType<FuncT, ArgsT...>::type
{
    
    //static_assert(1 == 0,  "bu" );    
    using IndiciesT = typename count_to<sizeof...(ArgsT) -1>::type;
    using ParamsT = tuple<ArgsT...>;    
    
    return explode_impl<FuncT, ParamsT>::apply(func, params, IndiciesT());
}


std::string test_func(int i, string j, int h)
{
   // cout << i1 << ", " << i2 << "\n";    
    
    return "placuszki";
}

int main()
{
    auto tup = std::make_tuple(1, "asdasd", 2);    
    //explode(test_func, tup);
    cout << "wynik: " << explode(test_func, tup) << "\n";

}
