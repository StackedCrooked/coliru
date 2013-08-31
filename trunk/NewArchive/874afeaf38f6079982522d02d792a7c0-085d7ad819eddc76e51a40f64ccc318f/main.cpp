#include <iostream>

class Test
{
public:
    Test(): b_(0) {}

    auto foo() const 
    { 
        return b_;    
    }    
private:
    int b_;
};

int main() 
{
    Test t;
    std::cout << t.foo();
}