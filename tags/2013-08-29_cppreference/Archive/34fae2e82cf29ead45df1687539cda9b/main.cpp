#include <iostream>
#include <string>

int main()
{
    std::string s = "Hello World!";
    for (auto i = std::begin(s), e = std::end(s); i != e; ++i)
    {
        std::cout << *i << " ";
    }
}