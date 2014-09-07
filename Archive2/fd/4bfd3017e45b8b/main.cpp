#include <iostream>
#include <type_traits>
#include <functional>
#include <tuple>

template <typename T>
struct lambda_traits : lambda_traits<decltype(&T::operator())> {};

template <typename C, typename R, typename... Args>
struct lambda_traits<R(C::*)(Args...)const>
{
    using result_type = R;
    
    static const int arity = sizeof...(Args);
    
    using args_tuple = std::tuple<Args...>;

    template <std::size_t index>
    struct arg
    {
        using type = typename std::tuple_element<index, args_tuple>::type;
    };
};

template <typename F>
auto foo(F bar)
-> typename std::enable_if<
          lambda_traits<F>::arity == 1
          && std::is_same<typename lambda_traits<F>::template arg<0>::type, float>::value
         >::type
{
    bar(3.14);
}

template <typename F>
auto foo(F bar)
-> typename std::enable_if<
          lambda_traits<F>::arity == 2
          && std::is_same<typename lambda_traits<F>::template arg<0>::type, int>::value
         >::type
{
    using T = typename lambda_traits<F>::template arg<1>::type;
    
    bar(5, (T)2.72f);
}

int main()
{
    auto lambda1 = [](float f) { std::cout << f << std::endl; };
    auto lambda2 = [](int i, float f) { std::cout << i << " " << f << std::endl; };
    
    foo(lambda1);
    foo(lambda2);
}
