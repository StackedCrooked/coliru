#include <iostream>
#include <locale>
#include <string>

int main()
{
    struct custom_bool : std::numpunct<char>
    {
        custom_bool( const char* true_name, const char* false_name )
             : true_name(true_name), false_name(false_name) {}

        const std::string true_name ;
        const std::string false_name ;

        protected:
          std::string do_truename() const override { return true_name ; }
          std::string do_falsename() const override { return false_name ; }
    };

    const bool flags[] = { true, false, false, true } ;
    const auto print_bools = [&flags]
    { for( bool b : flags ) std::cout << b << ' ' ; std::cout << '\n' ; };

    print_bools() ;

    std::cout << std::boolalpha ;
    print_bools() ;

    std::cout.imbue( { std::cout.getloc(), new custom_bool( "yes", "no") } );
    print_bools() ;

    std::cout.imbue( { std::cout.getloc(), new custom_bool( "da!", "nyet!") } );
    print_bools() ;

    std::cout << std::noboolalpha ;
    print_bools() ;
}
