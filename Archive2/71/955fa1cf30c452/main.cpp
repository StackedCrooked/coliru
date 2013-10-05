#include <iostream>
#include <locale>

// method one; works for integer types
void print_with_commas( unsigned int n )
{
    if( n < 1000 )
    {
        std::cout << n ;
    }
    else
    {
        int remainder = n % 1000 ;
        print_with_commas( n / 1000 ) ;
        std::cout << ',' << remainder ;
    }
}

int main()
{
    const int n = 123456789 ;

    print_with_commas(n) ;
    std::cout << '\n' ;

    {
        // method two; works for all numeric types

        // see: http://en.cppreference.com/w/cpp/locale/numpunct/grouping
        struct with_commas : std::numpunct<char>
        {
            protected:

               // group every three digits before the decimal point
               virtual std::string do_grouping() const override { return "\3"; }

               // use ',' as the group seperator
               virtual char do_thousands_sep() const override { return ',' ; }
        };

        // see: http://en.cppreference.com/w/cpp/io/basic_ios/imbue
        // http://en.cppreference.com/w/cpp/locale/locale/locale overload (7)
        // the locale calls delete on the facet when it is destroyed.
        std::cout.imbue( std::locale( std::cout.getloc(), new with_commas ) );

        std::cout << n << '\n' ;
    }
}
