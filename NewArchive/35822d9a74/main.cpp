#include <iostream>

class protected_base {};

class test : protected protected_base
{
public:
    test()
    {
        
        protected_base x;
        protected_base y = x;
        x = y;
        
    }
};

int main()
{
    test t;
}