#include <iostream>
#include <typeinfo>

float v[12];

decltype(auto) f()
{
    return v;
}

int main()
{
    std::cout <<typeid(decltype(f())).name() << std::endl;
}