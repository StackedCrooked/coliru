#include <iostream>

template <class T>
struct base
{
    base(T) { std::cout << "generic constructor\n"; }
};

template <>
base<int>::base(int) { std::cout << "int specialization\n"; }

template <class T>
struct Base : base<T>
{
    using base<T>::base;
};

int main() {
    Base<int> a(4);
    Base<char> b('a');
}
