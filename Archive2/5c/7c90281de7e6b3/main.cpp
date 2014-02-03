#include <iostream>
#include <string>
#include <vector>

union U
{
    int i;
    bool b;
    
    U() {}
    U(int i) : i(i) {}
    U(bool b) : b(b) {}
};

int main()
{    
    U u(true);
    
    std::cout << u.i << std::endl;
}
