#include <stdexcept>                                                             
#include <iostream>                                                              
#include <typeinfo>                                                              
                                                                                 
template<size_t P>                                                               
constexpr size_t short_value()                                           
{                                                                                
    return P;                                                                    
}                                                                                
                                                                                 
template<size_t V, char C, char... Cs>                                           
constexpr size_t short_value()                                           
{                                                                                
    return short_value<V*10+C-48, Cs...>();                                      
}                                                                               
                                                                                 
template<size_t V>                                                   
constexpr unsigned short short_value_check_cast()                                     
{                                                                                
    static_assert(V < 65536u, "Value too large for unsigned short");                      
    return static_cast<unsigned short>(V);
}                                                                                

template<char... Cs>                                                             
constexpr unsigned short operator "" _us()                                       
{                                                                                
    return short_value_check_cast<short_value<0, Cs...>()>();                                        
}                                                                                

int main()                                                                       
{                                                                                
    auto x = 12345_us;                                          
    auto y = 65535_us;                                                 
    std::cout << typeid(x).name() << std::endl;                                
    std::cout << x << std::endl;                                                 
    std::cout << y << std::endl;    
    //std::cout << 65536_us << std::endl; // compile error
}
                                                                                 
