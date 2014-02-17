#include <iostream>
#include <exception>

namespace{
    struct foo{
        void change_state() noexcept
        {
            throw std::exception();
        }
        ~foo(){
            std::cout << "Destructor called, saved state corrupted!" <<std::endl;
        }
    };
    
}


int main(){
   ::std::set_terminate([](){
       std::cout<< "Terminate called" <<std::endl;
   });
   
   foo f;
   f.change_state();
}