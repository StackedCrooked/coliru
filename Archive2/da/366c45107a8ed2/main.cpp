#include <memory>

class A ;

struct B
{
    std::unique_ptr<A> func() ;
    
    void func2() 
    {
        func() ;
    }
  
};

int main()
{
    B b1 ;
}