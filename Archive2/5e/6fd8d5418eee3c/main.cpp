#include <iostream>
#include <type_traits>
#include <functional>

template < typename R, typename... A, typename... Args >
typename std::enable_if< sizeof...( A ) == sizeof...( Args ), R >::type
call_my_function( R(*func)(A...), Args ...a )
{
    return func( a... );
}

int arg_count() { return 0; }
int arg_count(int) { return 1; }
int arg_count(int,int) { return 2; }

int main()
{
    std::cout << call_my_function( arg_count, 0 ) << std::endl;
    return 0;
}
