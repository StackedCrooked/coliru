#include <iostream>
#include <array>

void foo(int x[], int a, int b)
{
    
}

int main()
{    
    foo(std::array<int, 3>{1,2,3}.data(), 4, 5);
}
