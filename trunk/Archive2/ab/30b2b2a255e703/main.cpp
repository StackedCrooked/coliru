#include <cstddef>
#include <iostream>
#include <type_traits>

template
<
    std::size_t N,
    class Fun,
    class... Args,
    class = typename std::enable_if<sizeof...(Args) == N>::type
>
auto n_ary_fun(Fun fun, Args&&... args)
{
    return [&]() { return fun(std::forward<Args>(args)...); };
}

int main()
{
    auto lam1 = [](auto x)         { std::cout << x      << "\n"; };
    auto lam2 = [](auto x, auto y) { std::cout << x << y << "\n"; };
    
    auto f = n_ary_fun<1>(lam1, 1);     // OK
    auto g = n_ary_fun<2>(lam2, 1, 2);  // OK
    //auto h = n_ary_fun<2>(lam1, 1);     // ERROR
    //auto i = n_ary_fun<1>(lam2, 1, 2);  // ERROR
    
    f();        // prints 1 
    g();        // prints 2
}
