#include <iostream>
#include <locale>
#include <list>

// http://en.cppreference.com/w/cpp/locale/numpunct
struct custom_sep : std::numpunct<char>
{
    const char seperator = ',' ;
    const string_type grouping = "\3" ;

    explicit custom_sep( char_type seperator = ',', string_type grouping = "\3" )
                : seperator(seperator), grouping(grouping) {}

    protected:
        virtual char_type do_thousands_sep () const override { return seperator ; }
        virtual string_type do_grouping() const override { return grouping ; }
};

int main()
{
    std::list<long long> seq { 1000, 219038210, 87, 112348, -36, -1021456, 1234567890987654 } ;
    for( auto n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    // http://en.cppreference.com/w/cpp/io/ios_base/imbue
    std::cout.imbue( std::locale( std::cout.getloc(), new custom_sep ) ) ;
    for( auto n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    std::cout.imbue( std::locale( std::cout.getloc(), new custom_sep('.') ) ) ;
    for( auto n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    std::cout.imbue( std::locale( std::cout.getloc(), new custom_sep( ',', "\3\2" ) ) ) ;
    for( auto n : seq ) std::cout << n << "  " ; std::cout << '\n' ;
}
