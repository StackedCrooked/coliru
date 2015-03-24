#include <iostream>

template<typename... T>
void Foo(T...)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

template<typename... T>
void Bar(T... t)
{
    Foo(t...); // invokes Foo once with all arguments in the pack
    
    std::cout << "------------------\n";
    
    using swallow = int[];
    void(swallow{0, (void(Foo(t)), 0)...}); // invokes Foo once for each argument in the pack
}

int main() 
{
    Bar(1, 2L, 'a', "Hello");
}
