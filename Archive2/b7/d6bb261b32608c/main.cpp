#include <iostream>
#include <string>
#include <vector>

struct B
{
    virtual void copy(B const& rhs) = 0;
};

struct D : B
{
    void copy(B const& rhs)
    {
        D const *pd = dynamic_cast<D const*>(&rhs);
        if (pd) {
            y = pd->y;
        }
    }
    int y;
};

int main()
{
    D d1, d2; 
    d1.y = 2;
    d2.y = 5;
    
    B *p1(&d1), *p2(&d2); 
    
    ////////////////////////////////////////////
    (*p1).B::copy(*p2);
    ////////////////////////////////////////////
    
    return 0;
}
