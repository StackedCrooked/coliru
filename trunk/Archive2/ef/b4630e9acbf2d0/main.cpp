#include <iostream>                                                                                                                                                                                                                
    #include <cassert>    
    
    const size_t N = 500;
    
    //template <typename std::size_t N>                                                                                                                                                                                                  
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

    //template <typename std::size_t N>                                                                                                                                                                                                  
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
           // Mem<N> _mem; 
           Mem _mem;
    }; 
    
    
    
   // template <typename std::size_t N>                                                                                                                                                                                                  
thread_local
    //Mem<N> Tester<N>::_mem;    
    Mem Tester::_mem;

int main() {                                                                                                                                                                                                                       
    //Tester<500> t;                                                                                                                                                                                                                 
    Tester t;                                                                                                                                                                                                                 
    char * ptr  = t.getPtr();                                                                                                                                                                                                      
    char * buf = t.getBuf();                                                                                                                                                                                                       

    std::cout << "'" << (void*)ptr << std::endl;
    std::cout << "'" << (void*)buf << std::endl;
    assert( buf == ptr );                                                                                                                                                                                                          
}                                                                                                                                                                                                                                  
