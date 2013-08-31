#include <iostream>

int& foo(int&& n)
{
    ++n;
    return n;
}


int main()
{
    int& n = foo(3);
    std::cout << n << std::endl;    
}
