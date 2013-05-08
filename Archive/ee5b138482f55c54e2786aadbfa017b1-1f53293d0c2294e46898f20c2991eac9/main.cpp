#include <iostream>
#include <string>
#include <vector>

struct A {
    
    A () 
    {
        std::cerr << "A default" << std::endl;        
    }
    
    A (A const &a) 
    {
        std::cerr << "A copy" << std::endl;
    }
        
    A (A &&a) noexcept
    {
        std::cerr << "A move" << std::endl;        
    }
    
    ~A ()
    {
        std::cerr << "~A" << std::endl;        
    }
        
    A &operator= (A const &a)
    {
        std::cerr << "= copy" << std::endl;        
        return *this;
    }

    A &operator= (A &&a)
    {
        std::cerr << "= move" << std::endl;        
        return *this;
    }

    void mem () 
    {
        std::cerr << "A mem" << std::endl;        
    }
};

A func ()
{
    A a;
    return a;
}


int main()
{
    std::cerr << "1." << std::endl;
    
    {
        A a = func ();
        a.mem ();
    }
    
    std::cerr << "2." << std::endl;

    {
        A b;
        b = func ();
        b.mem ();
    }    
}
