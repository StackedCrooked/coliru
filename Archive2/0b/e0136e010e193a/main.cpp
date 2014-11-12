#include <vector>
#include <memory>
#include <iostream>

struct a
{
    ~a() { std::cout << "dtor\n" ; } 
} ;

int main()
{
    
    
    
    
    {
        std::vector<std::shared_ptr<a>> v1 ;
        std::shared_ptr<a> up1( new a ) ;
    std::shared_ptr<a> up2( new a ) ;
     v1.push_back( up1 ) ;
     v1.push_back( up2 ) ;
    }
    std::cout << "Boo\n" ;
    
}