#include <iostream>
#include <vector>

void foo(std::vector<auto> x)
{
    std::cout << x.front();
}

int main() 
{
    auto v = std::vector<int>{1, 2, 3};
    foo(v);
}