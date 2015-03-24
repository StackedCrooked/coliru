#include <cstdio>

#define print( a, b, ... ) ( std::printf( #a, (b) ) , std::printf( __VA_ARGS__ ) , std::puts("") )

int main()
{
    print( %d, 100, "%s %d and %c", ", ", 200, 'A' ) ;
    print( %s, "hello", " %s! %s %s!", "world", "hello", "again" ) ;
    print( %d, 1, " %d %d %d %d %d %d", 2, 3, 4, 5, 6, 7 ) ;
}
