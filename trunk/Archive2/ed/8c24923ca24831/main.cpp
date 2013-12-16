#include <iostream>
#include <stdexcept>

int& f() { throw std::invalid_argument("invalid"); static int i(50); return i; }

struct S
{
    S()
        try : r(f())
    { }
        catch(...)
    {
        std::cout << r;
    }
    int& r;
};

int main()
{
    try { S s; } catch(...) { }
}