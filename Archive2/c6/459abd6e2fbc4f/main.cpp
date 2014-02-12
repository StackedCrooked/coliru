#include <iostream>
#include <sstream>

int main()
{ 
    std::istringstream stm( "   2.675214  -2.638026 -1.912134 \n 1.8 4.5 -22.7 " ) ;
    
    float x, y, z ;
    while( stm >> x >> y >> z ) std::cout << x << ' ' << y << ' ' << z << '\n' ;
}
