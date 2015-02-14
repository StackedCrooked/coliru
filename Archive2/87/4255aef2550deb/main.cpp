#include <iostream>

struct asdf
{
    asdf(const asdf&)
    {
        std::cout << "asdf(const asdf&)\n";
    }
    
    asdf(bool)
    {
        std::cout << "asdf::asdf(bool)\n";
    }
};

int main()
{
    asdf(false);
}
