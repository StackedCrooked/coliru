#include <iostream>

struct foo
{
    int x, y;
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
};

struct bar
{
    int x[5];
    int y[5];
};

int main()
{
    std::cout << "foo size: " << sizeof(foo) << std::endl;
    std::cout << "bar size: " << sizeof(bar) << std::endl;
    
    return 0;
}