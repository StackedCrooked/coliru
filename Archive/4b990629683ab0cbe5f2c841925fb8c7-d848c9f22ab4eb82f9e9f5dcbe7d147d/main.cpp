
#include <iostream>

struct atype 
{
    int && x;
};

void info(int&)
{
    std::cout << "int&" << std::endl;
}

void info(int&&)
{
    std::cout << "int&&" << std::endl;
}

int main()
{
    info( static_cast<int&&>(atype{13}.x) );
    return 0;
}