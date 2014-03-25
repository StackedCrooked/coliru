#include <iostream>

int main()
{
    std::cout << std::boolalpha
               << "( -7 < 0 ): " << ( -7 < 0 ) << '\n' // true
               << "( -7 < 0U ): " << ( -7 < 0U ) << '\n'  // false
               << "( -7U < 0 ): " << ( -7U < 0U ) << '\n' ; // false 
}
