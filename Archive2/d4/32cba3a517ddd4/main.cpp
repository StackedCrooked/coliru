#include <iostream>
#include <memory>

struct Bar
{
    int x;
    
    void foo() { x++; }
    void baz() const { std::cout << x << std::endl; }
};

void foo(const std::unique_ptr<const Bar>& p)
{
    p->baz();
    p->foo();
    p->baz();
}

int main()
{
    std::unique_ptr<const Bar> p(new Bar[10]);
    foo(p);
    
    return 0;
}