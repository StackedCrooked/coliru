#include <iostream>
#include <string>

int main()
{
    std::string s = "Hello World!";
    using std::begin;
    using std::end;
    for (auto i = begin(s), e = end(s); i != e; ++i)
    {
        std::cout << *i << " ";
    }
}