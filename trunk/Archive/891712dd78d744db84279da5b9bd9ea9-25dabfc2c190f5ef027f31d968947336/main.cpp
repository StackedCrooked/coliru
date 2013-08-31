#include <iostream>
#include <array>
#include <functional>

template< typename ... args >
void tprintf( char const * fmt, args const & ... a ) {
    std::array< std::function< void() >, sizeof ... (a) > fmt_fun
        = { [&a]{ std::cout << a; } ... };

    for ( ; * fmt; ++ fmt ) {
        std::size_t fmt_n = * fmt - '0';
        fmt_fun[ fmt_n ](); // print nth argument
    }
}

int main() {
    tprintf( "021", "Hel", "rld!\n", "lo, wo" );
}
