#include <iostream>

struct C
{
    int i;
    C() : i(1) {}
    
    C& operator+=(const C& that)
    {
        i += that.i;
        return *this;
    }

    C operator+(const C& that) const &
    {
        C c(*this); // take a copy of this
        c += that;
        return c;
    }

/*
    C operator+(const C& that) &&
    {
        std::cout << "rvalue" << std::endl;
        (*this) += that;
        return std::move(*this); // moving this is ok here
    }
*/
};

C makeC()
{
    return C();
}

int main()
{
    C c;
    
    C x = makeC() + c;
    std::cout << x.i << std::endl;
}