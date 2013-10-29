#include <iostream>
#include <string>
#include <array>

typedef std::array<unsigned char, 6> Cont;

class A
{
public:
    A(const Cont &cont) : 
        mCont(cont)
    {}
    
    Cont mCont;
};

int main()
{
    A a({{0,1,2,3,4,5}});
    (void)a;
}
