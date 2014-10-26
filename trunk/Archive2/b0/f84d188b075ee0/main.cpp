#include <iostream>
#include <locale>
#include <iomanip>

// http://en.cppreference.com/w/cpp/locale/numpunct
struct space_separated : std::numpunct<char> 
{
    // http://en.cppreference.com/w/cpp/locale/numpunct/thousands_sep
    virtual char do_thousands_sep()   const override { return ' ' ; }  // separate with spaces
    
    // http://en.cppreference.com/w/cpp/locale/numpunct/grouping
    virtual std::string do_grouping() const override { return "\3"; } // in groups of 3 digits
};
 
int main()
{
    // http://en.cppreference.com/w/cpp/io/basic_ios/imbue
    std::cout.imbue( std::locale( std::locale( "en_GB.utf8" ), new space_separated ) ) ;
    
    // http://en.cppreference.com/w/cpp/io/ios_base/getloc
    const auto stdout_locale = std::cout.getloc() ;
    
    // http://en.cppreference.com/w/cpp/locale/use_facet
    // http://en.cppreference.com/w/cpp/locale/moneypunct
    const auto& mp_iternational = std::use_facet< std::moneypunct<char,true> >( stdout_locale ) ;
    const auto& mp_brief = std::use_facet< std::moneypunct<char> >( stdout_locale ) ;
    
    const double pounds = 1234567.89 ;
    const long double pence = pounds * 100 ;
    
    std::cout << std::fixed << std::setprecision(2) << "space separated, number: " << pounds << "\n\n"
              << "space separated, trailing currency, international: " << pounds << ' ' << mp_iternational.curr_symbol() << "\n\n"
              << "space separated, trailing currency, brief: " << pounds << mp_brief.curr_symbol() << "\n\n" 
              
              << "locale default, international: " << std::showbase << std::put_money( pence, true ) << "\n\n"
              << "locale default, brief: "  << std::put_money(pence) << '\n' ;
              // http://en.cppreference.com/w/cpp/io/manip/put_money
}
