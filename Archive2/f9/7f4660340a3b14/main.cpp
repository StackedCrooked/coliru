#include <iostream>
#include <tuple>
#include <stdio.h>



template<typename F, typename G>
auto compose(F&& f, G&& g)
{
    return [=]{ return f(), g(); };
}


template<typename F, typename G>
auto operator,(F&& f, G&& g) -> decltype(f(), g(), compose(f, g)) // put some restrictions on the type signature
{
    return compose(f, g);
}


int main()
{    
    auto abc = (
        []{ printf("a"); },
        []{ printf("b"); },
        []{ printf("c"); }
    );
    
    std::cout << "abc() => ";
    abc();
    
    
    std::cout << "\n(abc, abc)() => ";
    (abc, abc)();
}
