#include <iostream>

decltype(auto) foo()
{
    int x = 0;
    return x;
}

decltype(auto) bar()
{
    int x = 0;
    return (x);
}

template<typename T> // declaration for TD;
class TD; // TD == "Type Displayer"

template<typename T> // template w/types
void f(T& param) // of interest
{
    TD<T> tType; // cause T to be shown
    TD<decltype(param)> paramType; // ditto for param's type
}

int main()
{
    f(foo());
    f(bar());
    
    return 0;
}