#include <iostream>

struct B
{
    operator int()
    {   
        std::cout << "int()\n";
        return 1;
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

   /* operator int()
    {   
        std::cout << "int()\n";
        return 1;
    }   */

    C(int)
    {   
        std::cout << "C(int)\n";
    }   
};

int main()
{
    C c1; 
    std::cout << '\n';
    B b1;
    C c2 = b1; 
    std::cout << '\n';
    C c3(c1);
}
