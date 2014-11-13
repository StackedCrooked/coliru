#include <iostream>
 
void foo( const std::string & s )
{
    std::cout << s << std::endl;
}
 
template <typename ...U>
void foo( const std::string & s, const U & ... u )
{
    foo( s );
    foo( u... );
}
 
int main()
{
    foo( std::string( "Hello" ), 1 /* ", ", std::string( "World!" )*/ );
}
