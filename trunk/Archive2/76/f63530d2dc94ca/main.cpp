#include <iostream>

class Test {
public:
    operator int() const
    {
        return 42;
    }
};


int main()
{
    Test test;
    
    std::cout << (int)(test) << " "<< static_cast<int>(test) << std::endl;
}
