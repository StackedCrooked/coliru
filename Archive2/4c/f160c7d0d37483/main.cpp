#include <iostream>

struct S
{
    float x;
    
    S(float x): x(x) {}
};

int main()
{
    S s(3);
    std::cout << s.x;
    return 0;
}