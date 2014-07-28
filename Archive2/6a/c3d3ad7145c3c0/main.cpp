#include <iostream>
#include <cmath>
#include <typeinfo>
 
int main()
{
    int& (*fpi)(int*) = [](auto* a)->auto& { return *a; };
    [a](){std::cout<<a<<'\n';}();
}