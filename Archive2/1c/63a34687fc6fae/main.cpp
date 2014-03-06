#include <iostream>

struct Foo
{
    int x;
    Foo(int x): x(x) {}
    void SetX(int x) { x = x; }
};

int main()
{
    Foo f(3);
    std::cout << f.x << std::endl;
    f.SetX(4);
    std::cout << f.x << std::endl;
    
    return 0;
}