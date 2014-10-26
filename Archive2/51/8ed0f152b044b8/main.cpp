#include <tuple>
#include <utility>

template<typename F, typename... Args, int... Is>
void apply(F f, std::tuple<Args...> const& t, std::integer_sequence<int, Is...>)
{
    f(std::get<Is>(t)...);
}

template<typename F, typename... Args>
void apply(F f, std::tuple<Args...> const& t)
{
    apply(f, t, std::make_integer_sequence<int, sizeof...(Args)>{});
}

#include <iostream>
#include <string>

void foo(int i, std::string s, double d)
{
    std::cout << i << " " << s << " " << d;
}

int main()
{
    auto t = std::make_tuple(42, "Hello", 3.14);
    apply(foo, t);
}