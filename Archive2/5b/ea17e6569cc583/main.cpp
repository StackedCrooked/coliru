#include <iostream>

template <class T>
class base
{
    base(std::true_type, int) { std::cout << "int specialization\n"; }
    base(std::false_type, T) { std::cout << "generic constructor\n"; }

public:
    base(T t) : base(std::is_same<int, T>{}, std::move(t)) {}
};

template <class T>
struct Base : base<T>
{
    using base<T>::base;
};

int main() {
    Base<int> a(4);
    Base<char> b('a');
}
