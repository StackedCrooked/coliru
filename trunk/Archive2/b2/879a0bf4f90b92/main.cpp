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
    std::memset(&b, 0, sizeof(b));
    std::cout << "f: " << b.f << std::endl;
    std::cout << "i: " << b.i << std::endl;
    if(b.f == 0.0) std::cout << "equals";
    
    return 0;
}