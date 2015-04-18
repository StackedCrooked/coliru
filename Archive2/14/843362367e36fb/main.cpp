#include <iostream>

struct D
{
    D() 
    {   
        std::cout << "D()\n";
    }   

    explicit D(const D&) 
    {   
        std::cout << "D(const D&)\n";
    }   

    operator int()
    {   
        std::cout << "D int()\n";
        return 1;
    }   

    D(int)
    {   
        std::cout << "D(int)\n";
    }   
};

struct C
{
    C() 
    {   
        std::cout << "C()\n";
    }   

    explicit C(const C&) 
    {   
        std::cout << "C(const C&)\n";
    }   

   operator int()
    {   
        std::cout << "int()\n";
        return 1;
    }   

    C(int)
    {   
        std::cout << "C(int)\n";
    }   
};

int main()
{
    C c1; 
    std::cout << '\n';
    D d1;
    C c2 = d1; 
    std::cout << '\n';
    C c3(c1);
}
