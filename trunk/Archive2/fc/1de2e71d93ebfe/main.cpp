#include <iostream>
#include <memory>
#include <string>
 

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
    std::string foo = "hello";
    
    std::string baz = std::move(foo);
    
    std::cout << "foo: " << foo << std::endl
              << "baz: " << baz << std::endl;
    
    return 0;
}