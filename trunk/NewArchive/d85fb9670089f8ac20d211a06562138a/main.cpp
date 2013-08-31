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
    const c17 & ref = c17{};
    std::cout << sizeof(ref) << std::endl;
    std::cout << sizeof(wrap<c17>(ref)) << std::endl;
    std::cout << sizeof(bool&) << std::endl;
}