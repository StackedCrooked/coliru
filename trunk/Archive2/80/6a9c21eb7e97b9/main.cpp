#include <iostream>


template<typename T>
struct Wrap
{
    const T* operator->() const { return &t; }
    T* operator->() { return &t; }
    
    T t;
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
    Wrap<Foo> wrap_obj;
    wrap_obj->foo();
    
    Wrap<Foo>* wrap_ptr = &wrap_obj;
    wrap_ptr->foo();
}
