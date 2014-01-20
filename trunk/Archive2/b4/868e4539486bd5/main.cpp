#include "std_lib_facilities.h"

 int framed_area(int x, int y) 
{
    const int frame_width = 2;
    if( x-frame_width <= /*O*/ 0 || y-frame_width <= /*O*/ 0 )
           error( "non-positive area() argument called by framed_area()");
    return (x-frame_width) * (y-frame_width) ;
}

int main()
{
    std::cout << "\nframed area is: " << framed_area( 20, 30 ) << '\n' ;
}
