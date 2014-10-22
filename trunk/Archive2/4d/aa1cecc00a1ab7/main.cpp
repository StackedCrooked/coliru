#include <initializer_list>
#include <iostream>

template<typename T>
class Foo
{
public:
    Foo(T x)
    {
        std::cout << "int ctor" << std::endl;
    }
    
    Foo(std::initializer_list<T> x)
    {
        std::cout << "initializer_list" << std::endl;
    }    
};

int main()
{
    Foo<int>(42);
    Foo<int>{42};
    Foo<int>({42});
}
