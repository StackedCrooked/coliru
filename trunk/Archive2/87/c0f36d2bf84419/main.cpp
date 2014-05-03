#include <iostream>
#include <locale>
#include <list>

// http://en.cppreference.com/w/cpp/locale/numpunct
struct numpunct_seperated : std::numpunct<char>
{
        const char seperator = ',' ;
        const string_type grouping = "\3" ;

        numpunct_seperated( char_type sep = ',', string_type grp = "\3" )
                : seperator(sep), grouping(grp) {}

    protected:
        char_type do_thousands_sep () const override { return seperator ; }
        string_type do_grouping() const override { return grouping ; }
};

int main()
{
    std::list<int> seq { 1000, 219038210, 87, 11234, -36, -1021456 } ;
    for( int n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    // http://en.cppreference.com/w/cpp/io/ios_base/imbue
    std::cout.imbue( std::locale( std::cout.getloc(), new numpunct_seperated ) ) ;
    for( int n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    std::cout.imbue( std::locale( std::cout.getloc(), new numpunct_seperated('.') ) ) ;
    for( int n : seq ) std::cout << n << "  " ; std::cout << '\n' ;

    std::cout.imbue( std::locale( std::cout.getloc(), new numpunct_seperated( ',', "\3\2" ) ) ) ;
    for( int n : seq ) std::cout << n << "  " ; std::cout << '\n' ;
}
