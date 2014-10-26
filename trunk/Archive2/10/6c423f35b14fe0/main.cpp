#include <iostream>
#include <locale>
#include <iomanip>
 
struct space_separated : std::numpunct<char> 
{
    virtual char do_thousands_sep()   const override { return ' ' ; }  // separate with spaces
    virtual std::string do_grouping() const override { return "\3"; } // groups of 3 digits
};
 
int main()
{
    
    std::cout.imbue( std::locale( std::locale( "en_GB.utf8" ), new space_separated ) ) ;
    
    const auto stdout_locale = std::cout.getloc() ;
    const auto& mp_iternational = std::use_facet< std::moneypunct<char,true> >( stdout_locale ) ;
    const auto& mp_brief = std::use_facet< std::moneypunct<char> >( stdout_locale ) ;
    
    const double pounds = 1234567.89 ;
    const long double pence = pounds * 100 ;
    
    std::cout << std::fixed << std::setprecision(2) << "space separated, number: " << pounds << "\n\n"
              << "space separated, trailing currency, international: " << pounds << ' ' << mp_iternational.curr_symbol() << "\n\n"
              << "space separated, trailing currency, brief: " << pounds << mp_brief.curr_symbol() << "\n\n" 
              << "locale default, international: " << std::showbase << std::put_money( pence, true ) << "\n\n"
              << "locale default, brief: "  << std::put_money(pence) << '\n' ;
}
