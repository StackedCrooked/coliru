#include <iostream>

template<typename T>
struct outer;

namespace X
{
    template<typename T>
    void foo(typename outer<T>::inner)
    {
        std::cout << "foo\n";
    }
}

template<typename T>
struct outer
{
    struct inner {};
    
    friend void X::foo<T>(inner);
};

int main()
{
    outer<int>::inner x;
    foo(x);
}