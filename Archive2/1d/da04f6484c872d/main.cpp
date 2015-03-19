#include <iostream>


namespace X
{
    template<typename T>
    struct outer;
    template<typename T>
    void foo(typename outer<T>::inner)
    {
        std::cout << "foo\n";
    }
    template<typename T>
    struct outer
    {
        struct inner {
            friend void foo<T>(typename outer<T>::inner);
        };
    
    };
}

int main()
{
    X::outer<int>::inner x;
    foo(x);
}