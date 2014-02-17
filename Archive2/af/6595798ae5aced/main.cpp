#include <iostream>
#include <exception>

namespace{
    void foo() noexcept
    {
        throw std::exception();
    }
}


int main(){
   ::std::set_terminate([](){
       std::cout<< "Terminate called" <<std::endl;
   });
   
   foo();
    
}