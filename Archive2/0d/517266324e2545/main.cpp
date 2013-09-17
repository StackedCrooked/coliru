#include <cstdlib>
#include <iostream>
#include <memory>

void mystery2(int *p )
{
    int var = 3;
    p = &var;
    
}

int main()
{
    int *in = nullptr;
    mystery2(in);
    
    std::cout << &in;
}
