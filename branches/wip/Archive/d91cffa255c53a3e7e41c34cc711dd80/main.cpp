#include <iostream>

template<typename T>
struct wrap
{
    wrap(const T & t) : t(t) {}
    const T & t;
};

int main()
{
    typedef char c17[17];
    std::cout << sizeof(c17) << std::endl;
    std::cout << sizeof(wrap<c17>) << std::endl;
}