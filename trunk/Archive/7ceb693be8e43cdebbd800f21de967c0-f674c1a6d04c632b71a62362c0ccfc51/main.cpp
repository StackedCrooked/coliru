#include <iostream>
#include <string>

std::string function(std::string a) {
    if (a.size() == 0)
        return a;
    std::cout << "call ";
    return function(a.erase(a.size()-1));
}

int main()
{
    function("APPLES");
    std::cout << "pass";
}
