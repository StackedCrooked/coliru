#include <iostream>

struct X {
    X() {}
};

typedef int IsX;
template <class C>
IsX IsXTest(int /* dummy */, typename C::X* /* x */ = NULL)
{
    std::cout << "IsX" << std::endl;
    return 0;
}

typedef char IsNotX;
template <class C>
IsNotX IsXTest(long /* dummy */)
{
    std::cout << "IsNotX" << std::endl;
    return '\0';
}

int main()
{
    IsXTest<X>(0);
}