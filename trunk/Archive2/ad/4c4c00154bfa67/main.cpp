    #include <iostream>
    #include <iomanip>
    #include <bitset>
    #include <string>
    
    typedef union
    {
        double f;
        unsigned long long u;
        int long long i;
    } r;
     
    int main() 
    {
        r var1, var2;
    
        var1.f = -2 ; // High bits will be effected so we expect a large number for u
        
        std::cout << var1.u << std::endl ;
    
        std::bitset<sizeof(double)*8> b1( var1.u ) ;
        std::bitset<sizeof(double)*8> b2( 13835058055282163712ull ) ;
     
        std::cout << b1 << std::endl ;
        std::cout << b2 << std::endl ;
        
        var2.u = 3;
        
        var1.u = var1.u + var2.u; // Low bits will be effected so we expect a fraction
                                  // to appear in f
    
        std::cout << std::fixed << std::setprecision(17) <<  var1.f << std::endl ;
        
        std::bitset<sizeof(double)*8> b3( var1.u ) ;
        std::bitset<sizeof(double)*8> b4( 13835058055282163715ull ) ;
            
        std::cout << b3 << std::endl ;
        std::cout << b4 << std::endl ;
        
        return 0;
    }