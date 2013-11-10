#include <iostream>

int main()
{
    const float seq[] = { 900000.000f, 900000.100f, 900000.200f, 900000.300f, 900000.400f }  ;

    for( float f : seq ) std::cout << std::fixed << f << '\n' ;
}
