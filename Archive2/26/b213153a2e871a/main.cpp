#include <iostream>                                                                                                                                                                                                                
#include <cassert>    

template <typename std::size_t N>                                                                                                                                                                                                  
struct Mem {                                                                                                                                                                                                                       
    Mem() noexcept: ptr_(buf_) { 
        std::cout << "Initing Mem" << std::endl;
    }                                                                                                                                                                                                                              

    char * getBuf() {                                                                                                                                                                                                              
        return buf_;                                                                                                                                                                                                               
    }                                                                                                                                                                                                                              

    char * getPtr() {                                                                                                                                                                                                              
        return ptr_;                                                                                                                                                                                                               
    }                                                                                                                                                                                                                              

private:                                                                                                                                                                                                                           
    char buf_[N];                                                                                                                                                                                                                  
    char * ptr_;                                                                                                                                                                                                                   
};                                                                                                                                                                                                                                 

struct Tester {                                                                                                                                                                                                                    
    Tester() {                                                                                                                                                                                                                     
        std::cout << " Running Tester " << std::endl;                                                                                                                                                                              
    }                                                                                                                                                                                                                              

    char * getPtr() {                                                                                                                                                                                                              
        return _mem.getPtr();                                                                                                                                                                                                      
    }                                                                                                                                                                                                                              

    char * getBuf() {                                                                                                                                                                                                              
        return _mem.getBuf();                                                                                                                                                                                                      
    }                                                                                                                                                                                                                              
private:                                                                                                                                                                                                                           
    static thread_local 
       Mem<500> _mem; 
}; 
    
thread_local
    Mem<500> Tester::_mem;    

int main() { 
    Tester t;                                                                                                                                                                                                                 
    char * ptr  = t.getPtr();                                                                                                                                                                                                      
    char * buf = t.getBuf();                                                                                                                                                                                                       

    std::cout << "'" << (void*)ptr << std::endl;
    std::cout << "'" << (void*)buf << std::endl;
    assert( buf == ptr );                                                                                                                                                                                                          
}                                                                                                                                                                                                                                  
