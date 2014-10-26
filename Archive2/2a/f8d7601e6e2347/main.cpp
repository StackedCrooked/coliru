#include <utility>
#include <tuple>

namespace detail
{
    template<typename T, typename F, int... Is>
    void for_each(T&& t, F f, std::integer_sequence<int, Is...>)
    {
        auto l = { (f(std::get<Is>(t)), 0)... };
    }
}

template<typename... Ts, typename F>
void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
{
    detail::for_each(t, f, std::make_integer_sequence<int, sizeof...(Ts)>{});
}

#include <iostream>
#include <string>

struct my_functor
{
    template<typename T>
    void operator () (T const& t)
    {
        std::cout << t << std::endl;
    }
};

int main()
{
    std::tuple<int, double, std::string> t{42, 3.14, "Hello World!"};
    
    for_each_in_tuple(t, my_functor());
}
