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
    test instance;
    
    std::cout << reinterpret_cast<unsigned char*>(&(instance.x)) - reinterpret_cast<unsigned char*>(&instance) << std::endl;
    std::cout << reinterpret_cast<unsigned char*>(&(instance.y)) - reinterpret_cast<unsigned char*>(&instance) << std::endl;
    std::cout << reinterpret_cast<unsigned char*>(&(instance.z)) - reinterpret_cast<unsigned char*>(&instance) << std::endl;
}
