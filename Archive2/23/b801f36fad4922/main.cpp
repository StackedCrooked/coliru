#include <iostream>
#include <stdexcept>

struct S2 {
    S2() : i{9001} {std::cout << "Default\n";}  
    S2(int i_) : i{i_} {std::cout << "int\n";}
    
    int i;
};

S2& f() { throw std::invalid_argument("invalid"); static S2 i(50); return i; }

struct S
{
    S()
        try : r(f())
    { }
        catch(...)
    {
        std::cout << r.i;
    }
    S2& r;
};

int main()
{
    try { S s; } catch(...) { }
}