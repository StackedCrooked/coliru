#include <iostream>

template<typename T>
void f(T t) {
    std::cout << t << '\n';
    static_assert(std::is_same<T, int const*>::value, "T != int const*");
    static_assert(std::is_same<decltype(t), int const*>::value, "decltype(t) != int const*");
}

template<typename T>
void g(T t) {
    std::cout << t << '\n';
    static_assert(std::is_same<T, int>::value, "T != int");
    static_assert(std::is_same<decltype(t), int>::value, "decltype(t) != int");
    t++;
}

int main()
{
    int x = 22;
    int const* px = &x;

    f(px);

    int const& rx = x;
    g(rx);
}