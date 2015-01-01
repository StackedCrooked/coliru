#include <iostream>
#include <functional>

template <typename T>
struct combinator_traits : combinator_traits<decltype(&T::template operator()<T>)> {};

template <typename C, typename R, typename F, typename... Args>
struct combinator_traits<R(C::*)(F, Args...)const>
{
    using type = std::function<R(Args...)>;
};

// Tests:
template <typename T>
typename combinator_traits<T>::type Y(T t)
{
    return {};
}

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{    
    auto fib = [](auto myself, int x)
    {
        if(x < 2)
            return 1;
        return myself(myself, x - 1) + myself(myself, x - 2);
    };
    
    TD<decltype(Y(fib))>();
    
    std::function<int(int)> f = Y(fib);
}
