#include <iostream>

struct S
{
    operator void()
    {
        std::cout << "Hello!" << std::endl;
    }
};

int main()
{
    S s;
    (void)s;
}
