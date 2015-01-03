#include <iostream>
#include <memory>


void foo(const std::function<int()>& f) 
{
    std::cout << f() << std::endl;
}

void foo(const std::function<int(int x)>& f) 
{
    std::cout << f(5) << std::endl;
}

template<typename Callable>
auto baz(Callable c) 
    -> decltype(c(), void())
{
    std::cout << c() << std::endl;
}

template<typename Callable>
auto baz(Callable c) 
    -> decltype(c(5), void())
{
    std::cout << c(5) << std::endl;
}

int main() 
{
    foo([](){return 3;});
    foo([](int x){return x;});
    
    baz([](){return 3;});
    baz([](int x){return x;});
}