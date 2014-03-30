#include <iostream>

constexpr bool cstrcmp( char const * s1, char const * s2 ) {
    while ( *s2 && *s1 ) {
        if (*s1++ != *s2++ )
            return false;
    }
    return !*s1 && !*s2;
}
    
constexpr int str_to_val( char const * str ) {
    struct pair { char const*str; int value; };
    constexpr pair const tab[] { {"foo",1}, {"bar", 2} };
    for( auto & e : tab ) {
        if ( cstrcmp(str,e.str) )
            return e.value;
    }
    throw 0;
}

int main()
{
    constexpr auto test_0 = str_to_val("foo");
    constexpr auto test_1 = str_to_val("bar");
    //constexpr auto test_2 = str_to_val("baz"); // trigger compilation error
    std::cout << test_0 << " " << test_1 << std::endl;
}
