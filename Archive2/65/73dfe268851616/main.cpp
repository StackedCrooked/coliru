    #include <cmath>
    #include <cstdio>
    
    constexpr double f()
    {
        return std::pow( 2.0, 2.0 ) ;
    }
    
    int main()
    {
        constexpr double x = f() ;
        
        printf( "%f\n", x ) ;
    }