    #include <iostream>
    #include <limits>
    #include <cstdint>
    #include <type_traits>
    #include <tuple>
    
    /*
    constexpr unsigned int uLeftShift( unsigned int e1, int shift )
    {
        return e1 << shift ;
    }
    
    template <unsigned int e1, int shift, unsigned int result = uLeftShift(e1, shift)>
    constexpr unsigned int unsignedLeftShiftHelper(int)
    {
        return result ;
    }
    
    template <unsigned int e1, int shift>
    constexpr unsigned int unsignedLeftShiftHelper(...)
    {
        
        return e1 << ((sizeof(unsigned int)*8)-1) ;
    }
    
    template <unsigned int e1, int shift>
    constexpr unsigned int unsignedLeftShift()
    {
        
        return unsignedLeftShiftHelper<e1,shift>(0) ;
    }
    */
    
    constexpr unsigned int uLeftShift( unsigned int e1, int shift )
    {
        return e1 << shift ;
    }
    
    template <unsigned int e1, int shift, unsigned int result = uLeftShift(e1, shift)>
    constexpr std::tuple<unsigned int, bool> unsignedLeftShiftHelper(int)
    {
        return std::make_tuple<unsigned int, bool>(result,true) ;
    }
    
    template <unsigned int e1, int shift>
    constexpr std::tuple<unsigned int, bool> unsignedLeftShiftHelper(...)
    {
        
        return std::make_tuple<unsigned int, bool>(0,false) ;
    }
    
    template <unsigned int e1, int shift>
    constexpr std::tuple<unsigned int, bool> unsignedLeftShift()
    {
        
        return unsignedLeftShiftHelper<e1,shift>(0) ;
    }
    
    
    constexpr const char *str = "Hello World" ;      
  
    constexpr char accessHelper( int index )
    {
        return str[index] ;
    }
    
    template <int index, char result = accessHelper(index)>
    constexpr char access(int)
    {
        return result ;
    }
    
    template <int index>
    constexpr char access(...)
    {
        return str[0] ;
    }
    
    
    int main()
    {
        //constexpr std::intmax_t t = std::numeric_limits<std::intmax_t>::max() + 1 ;
        //constexpr std::intmax_t t = rightShift( 1, 35 )  ;
        
        /*
        constexpr unsigned int t1 = unsignedLeftShift<1,29>()  ;
        constexpr unsigned int t2 = unsignedLeftShift<1,33>()  ;
        constexpr unsigned int t3 = unsignedLeftShift<1,-2>()  ;
        
        std::cout << t1 << std::endl ;
        std::cout << t2 << std::endl ;
        std::cout << t3 << std::endl ;
        */
        
        constexpr std::tuple<unsigned int, bool> t1 = unsignedLeftShift<1,29>()  ;
        constexpr std::tuple<unsigned int, bool> t2 = unsignedLeftShift<1,33>()  ;
        constexpr std::tuple<unsigned int, bool> t3 = unsignedLeftShift<1,-2>()  ;
        
        std::cout << std::get<0>( t1 ) << ":" << std::get<1>(t1)  << std::endl ;
        std::cout << std::get<0>( t2 ) << ":" << std::get<1>(t2)  << std::endl ;
        std::cout << std::get<0>( t3 ) << ":" << std::get<1>(t3)  << std::endl ;
        
        std::cout << access<6>(0) << std::endl ;
        std::cout << access<20>(0) << std::endl ;
        
        //constexpr int num = std::numeric_limits<int>::max() * 2 ;
    }