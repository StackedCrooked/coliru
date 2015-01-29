#include <iostream>
#include <vector>

struct X
{
    template <typename U>
    void foo (U u) const
    {
        std::cout << "Hello " << u << std::endl;
    }
};

template <>
void X::foo <int> (int i) const
{
    std::cout << "Hello int " << i << std::endl;
}

int main()
{
    X().foo(1);
}