#include <iostream>

class Foo
{
public:
    Foo(): x(42), y(44) {}
private: 
int x,y;
};

int main()
{
    Foo f;
    int * bar = reinterpret_cast<int*>(&f);
    std::cout << *bar << '\n' <<  bar[1];
}