#include <iostream>
#include <tuple>
#include <stdio.h>


template<typename F, typename G>
auto operator,(F f, G g)
{
    return [=]{
        f();
        g();
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
