    #include <bitset>
    #include <iostream>
    
    union floatToInt
    {
       float f ;
       unsigned int u ;
    } ;
    
    int main()
    {
        floatToInt u1 ;
        
        u1.f = 3.4f ;
        
        std::bitset<32> bs1( u1.u ) ;
        
        std::cout << bs1 << std::endl ;
    }