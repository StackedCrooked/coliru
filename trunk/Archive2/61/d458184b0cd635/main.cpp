#include <utility>
#include <iostream>

template<typename F>
struct X
{
    X(F f) : _f(std::move(f)) { }
    
    template<typename... Ts>
    auto operator () (Ts&&... args)
    {
        _f(std::forward<Ts>(args)...);
    }
    
    F _f;
};

struct my_functor
{
    void operator () (double, double) 
    { std::cout << "(double, double)" << std::endl; }
};

int main()
{
    my_functor f1;
    X<my_functor> x(f1);
    x(1.0, 2.0);
    
    auto f2 = [] (char) { std::cout << "(char)" << std::endl; };
    X<decltype(f2)> y(f2);
    y('c');
}