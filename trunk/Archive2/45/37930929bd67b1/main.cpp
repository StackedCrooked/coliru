#include <iostream>

struct MyClass
{
    operator int() const
    {
        return 7;
    }
};

int main()
{
    MyClass mc;
    int x = mc;
    std::cout << "x = " << x << std::endl;
}
