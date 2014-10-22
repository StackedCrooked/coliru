#include <functional>
#include <cstddef>
#include <tuple>
#include <iostream>
#include <utility>

// generates lambda function that ignores parameter at given position
template <std::size_t N, typename Arg, typename R, typename... Args, std::size_t... Before, std::size_t... After, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(std::function<R(Args...)> f, std::index_sequence<Before...>, std::index_sequence<After...>)
    -> std::function<R(typename std::tuple_element<Before, Tuple>::type..., Arg, typename std::tuple_element<N + After, Tuple>::type...)>
{
    return [f] (auto&&... args)
                {
                    auto t = std::forward_as_tuple(std::forward<decltype(args)>(args)...); (void)t;
                    return f(static_cast<typename std::tuple_element<Before, decltype(t)>::type>(std::get<Before>(t))...,
                             static_cast<typename std::tuple_element<N + After + 1, decltype(t)>::type>(std::get<N + After + 1>(t))...);
                };
}

// overload for std::function wrapped functions:
template <std::size_t N, typename Arg, typename R, typename... Args, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(std::function<R(Args...)> f)
{
    return add_ignored_arg<N, Arg>(f, std::make_index_sequence<N>{}, std::make_index_sequence<sizeof...(Args) - N>{});
}

// overload for raw function pointers:
template <std::size_t N, typename Arg, typename R, typename... Args, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(R(*f)(Args...))
{
    return add_ignored_arg<N, Arg>(std::function<R(Args...)>(f), std::make_index_sequence<N>{}, std::make_index_sequence<sizeof...(Args) - N>{});
}

// tests:

struct B {};

void func(int i, char c, double d)
{
    std::cout << "func! " << i << " " << c << " " << d << std::endl;
}

void doSomething(std::function<void(int, char, B, double)> callback)
{
    callback(123, 'A', B{}, 3.14f);
}

void myDoSomething(std::function<void(int, char, double)> callback0)
{
    doSomething(add_ignored_arg<2, B>(callback0));
}

void foo(char c, double d)
{
    std::cout << "foo! " << c << " " << d << std::endl;
}

void bar(int i, double d)
{
    std::cout << "bar! " << i << " " << d << std::endl;
}

void qux(int i, char c)
{
    std::cout << "qux! " << i << " " << c << std::endl;
}

int main()
{
    myDoSomething(&func);
    
    // works even without std::function wrapper:
    add_ignored_arg<0, int>(&foo)(123, 'A', 3.14);
    add_ignored_arg<1, char>(&bar)(123, 'A', 3.14);
    add_ignored_arg<2, double>(&qux)(123, 'A', 3.14);
    
    // and chained, with decayed lambda:
    add_ignored_arg<2, double>(add_ignored_arg<1, char>(add_ignored_arg<0, int>(
        +[] () { std::cout << "lambda!" << std::endl; }
    )))(123, 'A', 3.14);
    
    // perfect-forwarding:
    add_ignored_arg<0, int>(
        +[] (B&& b) { std::cout << "perfectly-forwarded!" << std::endl; }
    )(123, B{});
}
