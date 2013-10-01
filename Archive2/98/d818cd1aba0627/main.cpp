#include <iostream>
#include <iomanip>
#include <locale>
#include <string>

int main()
{
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
    auto original_locale = std::cout.imbue( std::locale( std::cout.getloc(), new with_commas ) );

    const double ticket_price = 123.45 ;
    const int ticket_cnt = 26173 ;

    std::cout << "The total sales for Box seats were: $ " << std::fixed
               << std::setprecision(2) << ticket_cnt * ticket_price << '\n' ;

    // std::cout.imbue(original_locale) ;
    // ...
}
