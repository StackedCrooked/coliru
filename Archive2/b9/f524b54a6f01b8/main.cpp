#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;


double X( int param1 )
{
    return param1 * 2.2;
}
double Y( int param1, int param2 )
{
    return param1 * param2 * 1.2;
}

class ZED
{
     public:
        ZED(){}
        
        double ZX( int param1 ) // double ZX( z* this, int param1 );
        {
            return param1 * 1.2;
        }
        double ZY( int param1, int param2 )
        {
            return param1 * param2 * 1.2;
        }
        double ZZ( double param1, char param2, int param3 )
        {
            return 1.0;
        }
};

int main()
{
    std::function< double( int param1 ) > func;
    
    func = X;
    auto d = func( 1 );
    cout << d << endl;
    
    func = std::bind( &Y, _1, 5 );
    d = func( 1 ); // Y( 1, 5 );
    cout << d << endl;
    
    func = std::bind( &Y, 5, _1 );
    d = func( 10 ); // Y( 5, 10 );
    cout << d << endl;
    
    ZED obj;
    func = bind( &ZED::ZX, &obj, _1 );
    d = func( 1 ); // o.ZX( 1 );
    cout << d << endl;
    
    func = bind( &ZED::ZZ, &obj, 1.1, 'a', _1);
    d = func( 2 ); // o.ZZ( 1.1, 'a', 1 );
    cout << d << endl;
    return 0;
}

    
    
    
    
    
    
    

    