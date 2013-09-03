#include <iostream>
#include <string>
#include <algorithm>

double X(int i)
{
    return i * 2.0;
}

double Y(int i1, int i2)
{
    return ( i1 + i2 ) * 2.0;
}

class Z
{
public:
    Z(){}
    
    double ZX(int i)            // double ZX( Z* this, int i );
    {
        return i * 2.0;
    }
    double ZY(int i1, int i2)
    {
        return ( i1 + i2 ) * 2.0;
    }
    double ZZ(double d, char c, int i)
    {
        if ( c == 'A' )
            return d * i;
        return 0.0; 
    }
};

int main()
{
    std::function< double( int i ) > func;
    
    func = X;
    auto d = func( 1 );
    std::cout << d << std::endl;
    
    func = std::bind( &Y, std::placeholders::_1, 5 );
    d = func( 1 ); // Y( 1, 5 );
    std::cout << d << std::endl;
    
    func = std::bind( &Y, 6, std::placeholders::_1 );
    d = func( 2 );  // Y( 6, 2 );
    std::cout << d << std::endl;
    
    Z obj;
    func = std::bind( &Z::ZX, &obj, std::placeholders::_1 );
    d = func( 2 );  // obj.ZX( 2 );
    std::cout << d << std::endl;
    
    func = std::bind( &Z::ZY, &obj, 6.0, std::placeholders::_1 );
    d = func( 2 );  // obj.ZY( 6.0, 2 );
    std::cout << d << std::endl;
    
    func = std::bind( &Z::ZZ, &obj, 6.0, 'A', std::placeholders::_1 );
    d = func( 2 );  // obj.ZZ( 6.0, 'A', 2 );
    std::cout << d << std::endl;
    
    func = std::bind( &Z::ZZ, &obj, 6.0, 'B', std::placeholders::_1 );
    d = func( 2 );  // obj.ZZ( 6.0, 'B', 2 );
    std::cout << d << std::endl;
    
    
    std::string str = "Hallo";
    char eingabe = 'a';
    
    for_each( str.begin(), str.end(), [&] (const char& c)
    {
        if( c == eingabe )
            std::cout << "true" << std::endl; 
        else
            std::cout << "false" << std::endl;
    });
}



