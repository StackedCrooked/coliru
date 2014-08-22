#include <iostream>
#include <cstdlib>
#include <climits>
 
int main()
{
    std::cout << "abs(+3) = " << std::abs(3) << '\n'
              << "abs(-3) = " << std::abs(-3) << '\n';
 
//  std::cout << abs(INT_MIN)); // undefined behavior on 2's complement systems
}