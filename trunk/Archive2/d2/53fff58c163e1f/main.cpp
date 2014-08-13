#include <cstdio>

class Top
{ 
    virtual ~Top(){}    
};

class Left : public Top
{

};

class Right : public Top
{
    
};

int main() 
{
    Top t;
    Left l;
    Right r;
    
    if (dynamic_cast<Right*>(&l)) 
        printf("Class is derived from DerivedClass");
}
