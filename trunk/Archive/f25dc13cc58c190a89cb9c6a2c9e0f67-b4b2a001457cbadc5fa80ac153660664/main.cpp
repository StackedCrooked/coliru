#include <iostream>
#include <string>

struct Test
{
    Test(int i) : a(i) {}
    
    std::string to_string() const
    {
        return std::to_string(a) + std::to_string(b);
    }
    
    int a;
    bool b; // uninitialized!
};


int main()
{
    Test t(1);
    std::cout << t.a;
    std::cout << t.b;
}