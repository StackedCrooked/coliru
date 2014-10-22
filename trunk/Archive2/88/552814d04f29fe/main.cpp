#include <iostream>

template <template <typename T> class...>
struct my_class {};

template <typename T>
struct define_template
{
    template <typename U>
    class type {};
};

template <typename... T>
using new_class = my_class<define_template<T>::template type...>;

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    new_class<int, char> m;
    TD<decltype(m)>();
}
