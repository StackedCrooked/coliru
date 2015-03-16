#include <iostream>
#include <memory>

class Foo
{
public:
    Foo(){ std::cout << "Foo::Foo\n"; }
    ~Foo(){ std::cout << "Foo::~Foo\n"; }
    
    void bar(){ std::cout << "Foo::bar\n"; }
};

int main()
{
    std::shared_ptr<Foo> shared;
    std::cout << "shared declared\n";
    
    {
        std::shared_ptr<Foo> shared2(new Foo);
        shared2->bar();
        shared = shared2;
    }
    
    shared->bar();
    
    return 0;
}