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
                                                                                 
                                                                                 
template<size_t V, char... Cs>                                                   
constexpr unsigned short short_value_check()                                     
{                                                                                
    static_assert(short_value<V, Cs...>() < 65536u, "asdf");                      
    return short_value<V, Cs...>();                                               
/*    return short_value<V, Cs...>() < 65536u ? short_value<V, Cs...>()            
        : (throw std::logic_error(""));*/                                          
}                                                                                
                                                                                 

/*
template<char... Cs>                                                             
constexpr typename std::enable_if<(short_value_check<Cs...>() < 65536u),unsigned short>::type operator "" _us()
{                                                                                
    return static_cast<unsigned short>(short_value_check<0, Cs...>());                                        
}                                                                                
*/

template<char... Cs>                                                             
constexpr unsigned short operator "" _us()                                       
{                                                                                
    return short_value_check<0, Cs...>();                                        
}                                                                                

                                                                                 
int main()                                                                       
{                                                                                
    auto x = 12345_us;                                          
    auto y = 70000_us;                                                 
    std::cout << typeid(x).name() << std::endl;                                
    std::cout << x << std::endl;                                                 
    std::cout << y << std::endl;                                               
}                                                                                
                                                                                 
