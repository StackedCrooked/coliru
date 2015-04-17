#include <iostream>
#include <stdexcept>

struct f
{
    int a;
};

f foo(int a)
{
    switch (a)
    {
        {
            f result;
        case 1:
            result.a = 10;
            goto xyz;
            
        case 2:
            result.a = 20;
            goto xyz;
            
        xyz:
            return result;
        }
    default:
        throw std::runtime_error("lolollo");
    }
}

int main()
{
    f x = foo(2);
    std::cout << x.a << "\n";
    return 0;
}