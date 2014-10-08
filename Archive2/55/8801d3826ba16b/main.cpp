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


typedef std::integral_constant<int, 1> one_t;

int main()
{
    std::cout << one_t::value <<std::endl;
    
    auto lambda = [](auto x){ return x; };
    auto arity = fInfo<decltype(lambda)>::arity;
    
    std::cout << arity <<std::endl;
}