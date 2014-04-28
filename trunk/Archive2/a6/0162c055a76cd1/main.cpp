#include <iostream>


template<typename T>
struct Wrap
{
    const T* operator->() const { return &t; }
    T* operator->() { return &t; }
    
    T t;
};


template<typename T>
struct Wrap<Wrap<T>>
{
    Wrap<T> operator->() const { return t; }
    
    Wrap<T> t;
};


struct Foo
{
    void foo() const
    {
        std::cout << "Foo::foo" << std::endl;
    }
};

int main()
{
    Wrap<Wrap<Wrap<Foo>>> wrap_wrap_wrap;
    wrap_wrap_wrap->foo();
}
