#include <utility>
#include <iostream>

template<typename T>
class MyClass
{
    T impl;

public:
    explicit MyClass(T a) : impl(std::move(a)) { }

    T const& getImpl() const { return impl; }

    template<typename T0, typename T1>
    friend auto operator +(MyClass<T0> const& a, MyClass<T1> const& b) -> MyClass<decltype(a.impl + b.impl)>;
};

template<typename T0, typename T1>
auto operator +(MyClass<T0> const& a, MyClass<T1> const& b) -> MyClass<decltype(a.impl + b.impl)>
{
    return MyClass<decltype(a.impl + b.impl)>(a.impl + b.impl);
}

int main()
{
    MyClass<int> x(3);
    MyClass<long> y(5);

    std::cout << (x + y).getImpl() << '\n';
}
