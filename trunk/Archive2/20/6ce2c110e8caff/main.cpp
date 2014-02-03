#include <iostream>

template<int>
struct MyClass {};

template <int c>
double function(MyClass<c>&)
{
    if(c == 2)
        std::cout << "c is 2\n";
    else
        std::cout << "c is not 2\n";

    return 0.0;
}

int main() {
    MyClass<2> two;
    MyClass<3> three;
    
    function(two);
    function(three);
}