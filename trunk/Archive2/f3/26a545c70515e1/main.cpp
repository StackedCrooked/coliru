#include <iostream>

typedef int (*int_ptr)(int, int) ;

struct A
{
private:
    int (*_foo)(int a, int b);
    
public:
    operator int *()()
    {
        return _foo;
    }
};

int main(){ }