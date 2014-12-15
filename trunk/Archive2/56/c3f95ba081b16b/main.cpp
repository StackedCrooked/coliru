#include <iostream>
#include <memory>

struct A
{
    std::function<void()> fn;
    void foo() { std::cout << "A::foo\n"; }
};


std::unique_ptr<A> create()
{
    auto ret = std::unique_ptr<A>(new A);
    
    // line in question
    ret->fn = [&ret](){ ret->foo(); };
    
    return std::move(ret);
}   

int main(void)
{
    auto a = create();
    a->fn();
}
