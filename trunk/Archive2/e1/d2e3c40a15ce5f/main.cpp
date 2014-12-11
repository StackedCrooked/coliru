#include <iostream>
#include <string>
#include <vector>

class Weird
{
public:
    Weird(int v) : v(v)
    {
        std::cout << "Constructing" << v << std::endl;
    }
    
    operator int()
    {
        std::cout << "Reading " << v << std::endl;
        return v;
    }
    
    int v;
};

int main()
{
    std::cout << Weird(2) << Weird(3) << std::endl;
}
