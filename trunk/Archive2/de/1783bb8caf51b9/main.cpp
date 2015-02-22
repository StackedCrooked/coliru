#include <iostream>

struct C
{
    operator int()
    {
        std::cout << "C::operator int()" << std::endl;
        return 0;
    }
    operator void()
    {
        std::cout << "C::operator void()" << std::endl;
    }
};

int main()
{
    C c;
    (int)c;
    (void)c;
}