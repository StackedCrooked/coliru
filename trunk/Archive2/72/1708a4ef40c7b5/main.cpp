#include <iostream>
#include <string>
#include <vector>

class A
{
    public:
bool isTrue()
{
    return true;
}
};

void method(const A &a)
{
    
}

int main()
{
    bool a = false;
    A b;
    
    method(b);
}
    