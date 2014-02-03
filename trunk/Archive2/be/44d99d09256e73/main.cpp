#include <iostream>

class Nefarios
{
public:
    Nefarios()
    {
        std::cout << "created Nefarios" << std::endl;
    }
    ~Nefarios()
    {
        std::cout << "destroying Nefarios" << std::endl;
        throw 0;
    }
};

class Nefarios2
{
private:
    Nefarios n;
    
public:
    Nefarios2()
    {
        std::cout << "created Nefarios2" << std::endl;
    }
    ~Nefarios2()
    {
        std::cout << "destroying Nefarios2" << std::endl;
    }
};

int main()
{
    try
    {
        Nefarios2 n2;
    }
    catch(...)
    {
        std::cout << "OMG" << std::endl;
    }
    
    std::cout << "Nothing to see here move along" << std::endl;
    return 0;
}