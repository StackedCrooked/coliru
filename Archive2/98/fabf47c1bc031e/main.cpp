    #include <iostream>
    #include <limits>
    
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
    
    
    int main()
    {    
        std::cout << std::boolalpha <<  addIsDefined<int,int>::isDefined<10,10>() << std::endl ;
        std::cout << std::boolalpha <<  addIsDefined<int,int>::isDefined<std::numeric_limits<int>::max(),1>() << std::endl ;
        std::cout << std::boolalpha <<  addIsDefined<unsigned int,unsigned int>::isDefined<std::numeric_limits<unsigned int>::max(),std::numeric_limits<unsigned int>::max()>() << std::endl ;
    }
        