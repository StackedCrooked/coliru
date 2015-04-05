#include <functional>

int foo( int a ) { return a/2 + a%3 ; }

std::function< int(int) > closure() { return []( int a ) { return a/2 + a%3 ; } ; }
