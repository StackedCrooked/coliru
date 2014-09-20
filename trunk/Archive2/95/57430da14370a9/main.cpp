#include <iostream>
#include <string>
#include <typeinfo>

auto i = [](auto f) { return f; };
auto k = [](auto f) { return [=](auto g) { return f; }; };
auto s = [](auto f) { return [=](auto g) { return [=](auto h) { return f(h)(g(h)); }; }; };
auto dot = [](char c)  { return [=](auto f) { std::cout << c; return f; }; };
auto r = dot('\n');

int main()
{
    std::cout << typeid(i).name() << "\n";
    std::cout << typeid(k).name() << "\n";
    std::cout << typeid(s).name() << "\n";
    std::cout << typeid(i(i)).name() << "\n";
    std::cout << typeid(i(k)).name() << "\n";
    std::cout << typeid(k(i)).name() << "\n";
    std::cout << typeid(k(i)(k)).name() << "\n";
    std::cout << typeid(s(k)(k)(i)).name() << "\n";
    std::cout << typeid(s(k)(k)(k)).name() << "\n";

    dot('H')(dot('e'))(dot('l'))(dot('l'))(dot('o'))(dot(' '))(dot('w'))(dot('o'))(dot('r'))(dot('l'))(dot('d'))(r)(i);
    dot('*')(r);
}
