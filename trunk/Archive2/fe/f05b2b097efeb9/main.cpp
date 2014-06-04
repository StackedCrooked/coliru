#include <initializer_list>
#include <iostream>

struct Foo
{
    Foo(int, int)
    {
        std::cout << "Regular constructor." << std::endl;
    }
    
    Foo(std::initializer_list<int>)
    {
        std::cout << "Initializer list." << std::endl;
    }
};

struct Bar
{
    int x;
    int y;
};

int main()
{
    Foo foo{1, 2};
    Bar bar{3, 4};
    std::cout << "Initialized aggregate with " << bar.x << ", " << bar.y << std::endl;
}