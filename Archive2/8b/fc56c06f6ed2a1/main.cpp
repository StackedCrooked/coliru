#include <iostream>
#include <tuple>
#include <stdio.h>


template<typename F>
auto operator,(F f1, F f2)
{
    return [=]{
        f1();
        f2();
    };
}


int main()
{
    auto a = []{ std::cout << "a"; };
    
    (a)();
    
    puts("");
    
    (a, a)();
    
    puts("");
    
    (a, a, a)();
}
