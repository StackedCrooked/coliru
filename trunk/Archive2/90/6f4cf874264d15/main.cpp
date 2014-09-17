#include <iostream>
#include <type_traits>

template <typename T>
struct has_operator
{    
    template <typename U>
    struct SFINAE {};
    
    template <typename U>
    static std::true_type test(SFINAE<decltype(&U::operator())>*);

    template <typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), std::true_type>::value;
};

template <bool value, typename T>
struct check_constness;

template <typename T>
struct check_constness<false, T>
{   
    template <typename R, typename... Args>
    static std::false_type const_or_not(R(*)(Args...));
        
    template <typename R, typename... Args>
    static std::true_type const_or_not(const R(*)(Args...));
    
    static std::false_type const_or_not(...);

    using type = decltype(const_or_not( std::declval<T>() ));
};

template <typename T>
struct check_constness<true, T>
{    
    template <typename R, typename C, typename... Args>
    static std::false_type const_or_not(R(C::*)(Args...));
    
    template <typename R, typename C, typename... Args>
    static std::false_type const_or_not(R(C::*)(Args...) const);
    
    template <typename R, typename C, typename... Args>
    static std::true_type const_or_not(const R(C::*)(Args...));
    
    template <typename R, typename C, typename... Args>
    static std::true_type const_or_not(const R(C::*)(Args...) const);

    using type = decltype(const_or_not(&T::operator()));
};

template <typename T>
using is_const_ret_type = typename check_constness<has_operator<T>::value, T>::type;

int glob() { return 0; }
const int cglob() { return 0; }

int main()
{
    std::cout << std::boolalpha;
    
    auto lambda = []() -> int { return 0; };
    
    auto clambda = []() -> const int { return 0; };
  
    std::cout << is_const_ret_type<decltype(lambda)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(clambda)>::value << std::endl;
  
    std::cout << is_const_ret_type<decltype(&glob)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(&cglob)>::value << std::endl;
}
