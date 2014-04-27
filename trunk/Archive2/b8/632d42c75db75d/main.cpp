#include <cassert>


template<typename CRT>
struct Base
{
    void foo()
    {
        static_cast<CRT&>(*this).do_foo();
    }
    
private:
    Base() = default;
    ~Base() = default;
};


struct Foo : Base<Foo>
{    
    void do_foo()
    {
    }
};


int main()
{
    Foo foo;
    foo.foo();
}
