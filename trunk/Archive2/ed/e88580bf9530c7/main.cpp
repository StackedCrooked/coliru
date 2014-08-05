#include <iostream>
#include <cstring>

struct Banana
{
    float f;
    int i;
};

int main()
{
    Banana b;
    std::memset(&a, 0, sizeof(a));
    std::cout << "f: " << b.f << std::endl;
    std::cout << "i: " << b.i << std::endl;
    
    return 0;
}