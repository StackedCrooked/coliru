#include <iostream>

struct X
{
    X(int) { }
    X() : X(42) { throw 42; }
    ~X() { std::cout << "~X()"; }
};

int main()
{
    try
    {
        X x;
    }
    catch (int)
    {
    }
}
