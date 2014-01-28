    #include <iostream>
    #include <limits>
    #include <cstdint>
    #include <type_traits>
    
    constexpr unsigned int leftShift( unsigned int e1, unsigned int e2 )
    {
        return e1 << e2 ;
    }
    
    template <unsigned int e1, unsigned int e2, unsigned int result = leftShift(e1, e2)>
    constexpr unsigned int lShift(int, int)
    {
        return result ;
    }
    
    template <unsigned int e1, unsigned int e2>
    constexpr unsigned int lShift(...)
    {
        return e1 << ((sizeof(e2)*8)-1) ;
    }
    
    int main()
    {
        //constexpr std::intmax_t t = std::numeric_limits<std::intmax_t>::max() + 1 ;
        //constexpr std::intmax_t t = rightShift( 1, 35 )  ;
        constexpr unsigned int t = lShift<1,35>(0)  ;
        
        std::cout << t << std::endl ;
    }