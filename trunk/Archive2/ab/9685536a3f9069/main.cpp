#include <iostream>
#include <string>

class test
{
    public:
    
        test()
        {
        };
        
        int x;
        int y;
        int z;
};

int main()
{
    std::cout << &test::x << std::endl;
    std::cout << &test::y << std::endl;
    std::cout << &test::z << std::endl;
}
