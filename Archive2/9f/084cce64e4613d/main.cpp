#include <iostream>

template <typename R, typename... Args>
std::false_type const_or_not(R(*)(Args...));

template <typename R, typename C, typename... Args>
std::false_type const_or_not(R(C::*)(Args...));

template <typename R, typename C, typename... Args>
std::false_type const_or_not(R(C::*)(Args...) const);

template <typename R, typename... Args>
std::true_type const_or_not(const R(*)(Args...));

template <typename R, typename C, typename... Args>
std::true_type const_or_not(const R(C::*)(Args...));

template <typename R, typename C, typename... Args>
std::true_type const_or_not(const R(C::*)(Args...) const);
    
template <typename T>
using is_const_ret_type = decltype(const_or_not(&T::operator()));
    
int main()
{
    std::cout << std::boolalpha;
    
    auto lambda = []() -> int { return 0; };
    
    auto clambda = []() -> const int { return 0; };
  
    std::cout << is_const_ret_type<decltype(lambda)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(clambda)>::value << std::endl;
}
