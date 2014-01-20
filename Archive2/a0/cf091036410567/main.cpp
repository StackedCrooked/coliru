#include <iostream>
#include <type_traits>
#include <utility>

template <typename T>
struct container
{
    container(T const& v): value(v) {}
    T value;
};

template <typename T>
auto checked(std::ostream& out, container<T> const& c, int)
-> decltype( out << c.value )
{
    return out << "container[" << c.value << "]";
}

template <typename T>
std::ostream& checked(std::ostream& out, container<T> const&, short)
{
    return out << "container[unknown]";
}

template <typename T>
std::ostream& operator << (std::ostream& out, container<T> const& c)
{
    return checked(out, c, 0);
}

struct foo {};

int main()
{
    std::cout << "foo=" << container<foo>(foo()) << '\n';
    std::cout << "int=" << container<int>(int()) << '\n';
}