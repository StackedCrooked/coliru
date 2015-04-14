#include <iostream>
#include <cstdint>

struct f
{
    f(int& a)
        : ref(a)
    {
    }
    
    f& operator=(f const& other)
    {
        ref = other.ref;
        return *this;
    }
    
    f(f const& other)
        : ref(other.ref)
    {
    }
    
    int &ref;
};

int main()
{
    int a = 5;
    int b = 6;
    f one = a;
    f two = b;
    
    one = two;
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
}
