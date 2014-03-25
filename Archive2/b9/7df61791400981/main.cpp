#include <iostream>

enum class Month{jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov , dec};


int main()
{
    Month a = Month::feb;
    Month b = Month::jul;
    Month c = a;
    
    if( a != b ) std::cout << "a |= b" << '\n';
    if( a == c ) std::cout << "a == c" << '\n';
}