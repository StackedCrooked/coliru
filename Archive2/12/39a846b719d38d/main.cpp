#include <iostream>
#include <initializer_list>

template<class T>
struct Wrapper
{
    T value;
    Wrapper() {}
    Wrapper(std::initializer_list<std::initializer_list<T>> /*unused*/) : value() {}
    Wrapper(T const &value) : value(value) { }
    // ... operators defined here ...
};
 
int main()
{
    unsigned int x1; 
    unsigned int x2{};
    Wrapper<unsigned int> y1, y2 = Wrapper<unsigned int>();
    auto y3 = Wrapper<unsigned int>({});

    std::cerr << x1       << std::endl;  // uninitialized, as expected
    std::cerr << y1.value << std::endl;  // uninitialized, as expected

    std::cerr << x2       << std::endl;  // zero-initialized, as expected
    std::cerr << y2.value << std::endl;  // uninitialized!?!
    std::cerr << y3.value << std::endl;  // zero-initialized, as expected
}
