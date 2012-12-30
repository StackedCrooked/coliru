#include <iostream>
#include <string>

int main()
{
    std::string s = "Hello World!";
    for (auto i = begin(s), e = end(s); i != e; ++i)
    {
        std::cout << *i << " ";
    }
}