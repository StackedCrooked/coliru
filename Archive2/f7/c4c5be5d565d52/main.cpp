#include <functional>
#include <utility>
#include <iostream>

template <typename... Types, std::size_t... indexes,  typename Functor>
void apply(std::function<void(Types...)> f, std::index_sequence<indexes...>, Functor&& functor)
{
    f(static_cast<Types>(std::forward<Functor>(functor)(indexes))...);
}

template <typename... Types, typename Functor>
void apply(std::function<void(Types...)> f, Functor&& functor)
{
    apply(f, std::make_index_sequence<sizeof...(Types)>{}, std::forward<Functor>(functor));
}

void foo(int a, long b, short c)
{
    std::cout << a << b << c << std::endl;
}

int main()
{
    std::function<void(int, long, short)> bar = foo;
    
    apply(bar, [](std::size_t index){ return (int)index; });
}