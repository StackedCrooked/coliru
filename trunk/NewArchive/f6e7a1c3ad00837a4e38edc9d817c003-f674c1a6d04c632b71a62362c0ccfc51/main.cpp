#include <iostream>
#include <string>

std::string function(std::string a, int count) {
    if (count == 0)
        return a;
    std::cout << "call ";
    return function(a, count-1);
}

int main()
{
    std::cout << function("APPLES", 3);
    std::cout << " pass";
}
