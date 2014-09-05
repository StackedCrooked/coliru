template<typename T>
struct manual
{
    T t;
    template<typename U>
    auto operator()(U u) { u(t); }
};

auto terminal = [](auto term)           
{
    return manual<decltype(term)>{term};
};

#include <iostream>

int main()
{
    auto foo = [](auto x) { std::cout << x << "\n"; };
    terminal(2)(foo);
}