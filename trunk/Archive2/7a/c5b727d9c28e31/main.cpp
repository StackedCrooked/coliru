#include <iostream>
#include <string>
#include <vector>

constexpr int expression(int n)
{
    return n == 0 ? 1 : expression(n - 1) * n;
}


int main()
{
    std::cout << "Value of some constexpr " << expression(5) << std::endl;   
}
