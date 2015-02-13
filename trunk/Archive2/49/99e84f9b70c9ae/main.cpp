#include <iostream>
#include <string>
#include <vector>

bool funcA()
{
    std::cout << "A";
    return false;
}

bool funcB()
{
    std::cout << "B";
    return true;
}

int main()
{
    if(funcA() || funcB())
    {
        std::cout << "j";
    }
}
