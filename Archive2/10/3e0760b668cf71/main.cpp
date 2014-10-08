#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <stack>
#include <type_traits>


template <typename F>
struct fInfo : fInfo<decltype(&F::operator())> { };

template <typename F, typename Ret, typename... Args>
struct fInfo<Ret(F::*)(Args...)const> { static const int arity = sizeof...(Args); };

template <typename F, typename... Args>
struct autofInfo : fInfo<decltype(&F::template operator()<Args...>)> {};



typedef std::integral_constant<int, 3> three_t;

template<typename T>
void test(T lambda)
{
    std::cout << three_t::value <<std::endl;
    
    

    constexpr auto arity = autofInfo<decltype(lambda), int>::arity;
    
    std::enable_if_t<three_t::value == arity>* a;
    
    std::cout << arity <<std::endl;
    
    std::enable_if_t<autofInfo<decltype(lambda), int>::arity == three_t::value>* b;
}

int main()
{
    auto lambda = [](int x, int y, float z) { return x + y + z; };
    test(lambda);
}