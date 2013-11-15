#include <iostream>
#include <vector>
#include <array>

class X
{
public:
    X()
    { std::cout << "!"; }
};

int main()
{
    std::cout << "C-table" << std::endl;
    X a[10];
    std::cout << std::endl;
    
    std::cout << "vector" << std::endl;
    std::vector<X> b(10);
    //std::vector<X> b;
    //b[9] = X();
    std::cout << std::endl;
    

    std::cout << "array" << std::endl;
    std::array<X, 10> c;
    std::cout << std::endl;

    return 0;
}
