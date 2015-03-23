#include <iostream>
#include <memory>
 

class Foo
{
public:
    Foo(Foo&&) = default;
    
    Foo(const Foo&) = delete;
    
    Foo(int x) : bar(x){}
    
    ~Foo() {}
    
    int bar;
};

int main()
{
    Foo foo(7);
    
    Foo baz(std::move(foo));
    
    std::cout << "foo: " << foo.bar << std::endl
              << "baz: " << baz.bar << std::endl;
    
    return 0;
}