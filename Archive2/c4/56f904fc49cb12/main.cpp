#include <iostream>
#include <memory>

struct Char
{
    constexpr Char( char c = ' ' ) noexcept : value(c) {}

    constexpr operator char () const noexcept { return value ; }
    operator char& () noexcept { return value ; }

    constexpr char as_char() const noexcept { return value ; }

    char value ;
};

inline bool operator== ( const Char& a, const Char& b ) noexcept { return std::addressof(a) == std::addressof(b) ; }
inline bool operator!= ( const Char& a, const Char& b ) noexcept { return !(a==b) ; }

inline bool operator== ( const Char& a, const char& b ) noexcept { return std::addressof(a.value) == std::addressof(b) ; }
inline bool operator!= ( const Char& a, const char& b ) noexcept { return !(a==b) ; }

inline bool operator== ( const char& a, const Char& b ) noexcept { return b == a ; }
inline bool operator!= ( const char& a, const Char& b ) noexcept { return !(a==b) ; }

int main()
{
    Char array[2] = { '*', '*' } ;
    if( array[0] != array[1] ) std::cout << "not equal\n" ; // not equal
    if( char(array[0]) == array[1].as_char() ) std::cout << "equal\n" ; // equal

    char c = '*' ;
    if( array[0] != c ) std::cout << "not equal\n" ; // not equal
    if( array[0].as_char() == c ) std::cout << "equal\n" ; // equal

    array[0] = 'a' ;
    if( array[0].as_char() != char(array[1]) ) std::cout << "not equal\n" ; // not equal
    if( char(array[0]) == 'a' ) std::cout << "equal\n" ; // equal
}
