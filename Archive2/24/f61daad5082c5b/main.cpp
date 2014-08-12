#include <iostream>
#include <cmath>
 
int main()
{
    // normal usage: the signs of the two arguments determine the quadrant
    std::cout << "(+1,+1) cartesian is (" << hypot(1,1)
              << ',' << atan2(1,1) << ") polar\n"  // atan2(1,1) = +pi/4, Quad I
              << "(+1,-1) cartesian is (" << hypot(1,-1)
              << ',' << atan2(1,-1) << ") polar\n" // atan2(1, -1) = +3pi/4, Quad II
              << "(-1,-1) cartesian is (" << hypot(-1,-1)
              << ',' << atan2(-1,-1) << ") polar\n" // atan2(-1,-1) = -3pi/4, Quad III
              << "(-1,1) cartesian is (" << hypot(-1,1)
              << ',' << atan2(-1,1) << ") polar\n"; // atan2(-1,-1) = -pi/4, Quad IV
    // special values
    std::cout << "atan2(0, 0) = " << atan2(0,0)
              << " atan2(0,-0) = " << atan2(0,-0.0) << '\n'
              << "atan2(7, 0) = " << atan2(7,0)
              << " atan2(7,-0) = " << atan2(7,-0.0) << '\n';
}