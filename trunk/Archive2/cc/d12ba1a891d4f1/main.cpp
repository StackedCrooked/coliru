#include <iostream>
#include <functional>

std::string& test()
{
    std::string s = "original.";
    std::cout << s;
    return std::ref(s);
}

int main()
{
    test()[0] = "h";
    return 0;
}
