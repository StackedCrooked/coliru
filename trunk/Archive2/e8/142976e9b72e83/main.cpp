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

template <typename F>
struct autofInfo<F>{};

template <typename F, typename... Args>
struct autofInfo : fInfo<decltype(&F::template operator()<Args...>)> {};


typedef std::integral_constant<int, 1> one_t;

template<typename T, 
std::enable_if_t<autofInfo<T, std::string>::arity == one_t::value>* = nullptr
>
void test(T lambda)
{
    std::cout << "one arg" << one_t::value <<std::endl;

    constexpr auto arity = autofInfo<decltype(lambda), std::string>::arity;
    
    std::enable_if_t<one_t::value == arity>* a;
    
    std::cout << arity <<std::endl;
    
    std::enable_if_t<autofInfo<decltype(lambda), std::string>::arity == one_t::value>* b;
}

template<typename T, 
std::enable_if_t<autofInfo<T>::arity != one_t::value>* = nullptr
>
void test(T lambda)
{
    std::cout << "void" << one_t::value <<std::endl;

    constexpr auto arity = autofInfo<decltype(lambda)>::arity;
    
    std::enable_if_t<one_t::value == arity>* a;
    
    std::cout << arity <<std::endl;
    
    std::enable_if_t<autofInfo<decltype(lambda)>::arity == one_t::value>* b;
}


int main()
{
    auto lambda1 = [](auto x) { return x;};
    auto lambda2 = []() { return std::string{}; };
    test(lambda1);
  //  test(lambda2);    
}