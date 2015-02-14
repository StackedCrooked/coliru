#include <iostream>

struct asdf
{
    asdf(bool b) { std::cout << "bool" << std::endl; }
    asdf(const asdf& other) { std::cout << "copy" << std::endl; }
};

int main()
{
    asdf foo(false);
    return 0;
}