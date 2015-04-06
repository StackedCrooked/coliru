#include <iostream>
#include <string>
 
bool next( std::string &n, size_t pos )
{
    if( n[pos]++ < '9' ) return true;
    if( pos == 0 ) return false;
    if( next( n, pos - 1 ) ) {
        n[pos] = n[pos-1];
        return true;
    }
    return false;
}
 
bool next( std::string &n )
{
    return next( n, n.length() - 1 );
}
 
int main()
{
    std::string number="555";
 
    while( next( number ) ) {
        std::cout << number << std::endl;
    }
    return 0;
}
