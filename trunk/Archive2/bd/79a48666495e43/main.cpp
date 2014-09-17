#include <iostream>
#include <type_traits>
#include <utility>

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

template <typename T, typename... Args>
struct has_templated_operator
{    
    template <typename U>
    struct SFINAE {};
    
    template <typename U>
    static std::true_type test(SFINAE<decltype(&U::template operator()<Args...>)>*);

    template <typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), std::true_type>::value;
};

template <bool normal, bool templated, typename T, typename... Args>
struct check_constness;

template <typename T, typename... Args>
struct check_constness<false, false, T, Args...>
{        
    template <typename R, typename... Params>
    static std::true_type const_or_not(const R(*)(Params...));
    
    static std::false_type const_or_not(...);

    using type = decltype(const_or_not(std::declval<T*>()));
};

template <typename T, typename... Args>
struct check_constness<true, false, T, Args...>
{        
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...));
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) const);
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) const volatile);
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) volatile);
    
    static std::false_type const_or_not(...);

    using type = decltype(const_or_not(&T::operator()));
};

template <typename T, typename... Args>
struct check_constness<false, true, T, Args...>
{        
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...));
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) const);
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) const volatile);
    
    template <typename R, typename C, typename... Params>
    static std::true_type const_or_not(const R(C::*)(Params...) volatile);
    
    static std::false_type const_or_not(...);

    using type = decltype(const_or_not(&T::template operator()<Args...>));
};

template <typename T, typename... Args>
using is_const_ret_type = typename check_constness<has_operator<T>::value, has_templated_operator<T, Args...>::value, T, Args...>::type;

int glob() { return 0; }
const int cglob() { return 0; }

int main()
{
    std::cout << std::boolalpha;
    int x = 123;
    
    auto lambda = []() -> int { return 0; };
    
    auto clambda = []() -> const int { return 0; };
    
    auto closure = [x]() -> int { return x; };
    
    auto cclosure = [x]() -> const int { return x; };
    
    auto variadic = [x](auto&&... a) -> int { return x; };
    
    auto cvariadic = [x](auto&&... a) -> const int { return x; };
    
    auto conditional = [x](auto&&... a) -> std::conditional_t<sizeof...(a) >= 1, const int, int> { return 0; };
  
    std::cout << is_const_ret_type<decltype(lambda)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(clambda)>::value << std::endl;
  
    std::cout << is_const_ret_type<decltype(glob)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(cglob)>::value << std::endl;
  
    std::cout << is_const_ret_type<decltype(closure)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(cclosure)>::value << std::endl;
  
    std::cout << is_const_ret_type<decltype(variadic)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(cvariadic)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(conditional)>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(conditional), int>::value << std::endl;
    
    std::cout << is_const_ret_type<decltype(conditional), decltype(1), decltype(3.14)>::value << std::endl;
}
