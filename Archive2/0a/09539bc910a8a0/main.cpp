#include <iostream>

struct foo
{
    foo() : x(), y(), z() {}
    foo(int x, int y, int z) : x(x), y(y), z(z) {}
    
    int x;
    int y;
    int z;
    
    void clear() { *this = foo(); }
};

int main()
{
    foo f(10, 20, 30);
    
    std::cout << f.x << ' ' << f.y << ' ' << f.z << '\n';
    f.clear();
    std::cout << f.x << ' ' << f.y << ' ' << f.z << '\n';
}
