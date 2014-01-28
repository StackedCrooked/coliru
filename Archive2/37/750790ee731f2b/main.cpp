    #include <iostream>
    #include <limits>
    #include <cstdint>
    #include <type_traits>
    
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
    
    template <typename T1, typename T2>
    constexpr T1 LeftShift( T1 e1, T2 shift )
    {
        return e1 << shift ;
    }
    
    template <typename T1, typename T2>
    struct LeftShiftIsDefined
    {
         template <T1 t1, T2 t2>
         static constexpr bool isDefined()
         {
             return isDefinedHelper<t1,t2>(0) ;
         }
        
         template <T1 t1, T2 t2, T1 result = LeftShift( t1, t2 )>
         static constexpr bool isDefinedHelper(int)
         {
             return true ;
         }
         
         template <T1 t1, T2 t2>
         static constexpr bool isDefinedHelper(...)
         {
             return false ;
         }
    };
    
    template <unsigned int e1, int shift, unsigned int result = LeftShift(e1, shift)>
    constexpr bool uLeftShiftDefinedHelper(int)
    {
        return true ;
    }
    
    template <unsigned int e1, int shift>
    constexpr bool uLeftShiftDefinedHelper(...)
    {
        
        return false;
    }
    
    template <unsigned int e1, int shift>
    constexpr bool uLeftShiftDefined()
    {
        
        return uLeftShiftDefinedHelper<e1,shift>(0) ;
    }
    
    template <int e1, intmax_t shift, int result = LeftShift(e1, shift)>
    constexpr bool sLeftShiftDefinedHelper(int)
    {
        return true ;
    }
    
    template <int e1, int shift>
    constexpr bool sLeftShiftDefinedHelper(...)
    {
        
        return false;
    }
    
    template <int e1, int shift>
    constexpr bool sLeftShiftDefined()
    {
        return sLeftShiftDefinedHelper<e1,shift>(0) ;
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
    
    template <typename T1, typename T2>
    constexpr auto Add( T1 t1, T2 t2 ) -> decltype( t1 + t2 )
    {
        return t1 + t2;
    }
    
    template <typename T1, typename T2>
    struct addIsDefined
    {
         template <T1 t1, T2 t2>
         static constexpr bool isDefined()
         {
             return isDefinedHelper<t1,t2>(0) ;
         }
        
         template <T1 t1, T2 t2, decltype( t1 + t2 ) result = Add( t1, t2 )>
         static constexpr bool isDefinedHelper(int)
         {
             return true ;
         }
         
         template <T1 t1, T2 t2>
         static constexpr bool isDefinedHelper(...)
         {
             return false ;
         }
    };
    
    size_t fibo_runtime(size_t num)
    {
      return num ;
    }
    
    template <typename T>
    constexpr T fib(T num)
    {
        return num <= 1 ? 1 : num*fib<T>(num - 1)  ;
    }
    
    
    size_t fib(size_t num)
    {
        return fibo_runtime( num ) ;
    }
    
    int main()
    {
        std::cout << fib(3) << std::endl ;
        
        size_t x = 10 ;
        std::cout << fib(x) << std::endl ;
        
        std::cout << std::boolalpha <<  addIsDefined<int,int>::isDefined<10,10>() << std::endl ;
        std::cout << std::boolalpha <<  addIsDefined<int,int>::isDefined<std::numeric_limits<int>::max(),1>() << std::endl ;
        std::cout << std::boolalpha <<  addIsDefined<unsigned int,unsigned int>::isDefined<std::numeric_limits<unsigned int>::max(),std::numeric_limits<unsigned int>::max()>() << std::endl ;
        
        std::cout << std::endl ;
        
        
        //constexpr int x = std::numeric_limits<int>::min() % 0 ;
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

        /*
        constexpr std::tuple<unsigned int, bool> t1 = unsignedLeftShift<1,29>()  ;
        constexpr std::tuple<unsigned int, bool> t2 = unsignedLeftShift<1,33>()  ;
        constexpr std::tuple<unsigned int, bool> t3 = unsignedLeftShift<1,-2>()  ;
        
        std::cout << std::get<0>( t1 ) << ":" << std::get<1>(t1)  << std::endl ;
        std::cout << std::get<0>( t2 ) << ":" << std::get<1>(t2)  << std::endl ;
        std::cout << std::get<0>( t3 ) << ":" << std::get<1>(t3)  << std::endl ;
        */
        
        std::cout << std::boolalpha << LeftShiftIsDefined<unsigned int, int>::isDefined<1u,29>() << std::endl ;
        std::cout << std::boolalpha << LeftShiftIsDefined<unsigned int, int>::isDefined<1u,64>() << std::endl ;
        std::cout << std::boolalpha << LeftShiftIsDefined<unsigned int, int>::isDefined<1u,-2>() << std::endl ;
        std::cout << std::boolalpha << LeftShiftIsDefined<unsigned long long, int>::isDefined<1ull,63>() << std::endl ;
        std::cout << std::boolalpha << LeftShiftIsDefined<unsigned long long, int>::isDefined<1ull,64>() << std::endl ;
        std::cout << std::endl ;
        
        /*
        std::cout << std::boolalpha << uLeftShiftDefined<1u,29>() << std::endl ;
        std::cout << std::boolalpha << uLeftShiftDefined<1u,64>() << std::endl ;
        std::cout << std::boolalpha << uLeftShiftDefined<1u,-2>() << std::endl ;
        
        std::cout << std::boolalpha << sLeftShiftDefined<1,29>() << std::endl ;
        std::cout << std::boolalpha << sLeftShiftDefined<1,64>() << std::endl ;
        std::cout << std::boolalpha << sLeftShiftDefined<1,-2>() << std::endl ;
        std::cout << std::boolalpha << sLeftShiftDefined<-1,1>() << std::endl ;
        */
        
        

        std::cout << access<6>(0) << std::endl ;
        std::cout << access<20>(0) << std::endl ;
        
       //constexpr int x1 = -1 << 1 ;
       //constexpr int x2 = -1 >> 2 ;
        
        //constexpr int num = std::numeric_limits<int>::max() * 2 ;
    }