#include <iostream>
#include <locale>
#include <string>

int main()
{
    // http://en.cppreference.com/w/cpp/locale/numpunct
    struct numpunct_with_commas : std::numpunct<char>
    {
        protected:
            virtual std::string do_grouping() const override
            {
                // three digits in the right-most group, two digits in each group to the left
                static const std::string grouping = "\3\2" ;
                return grouping ;
            }

            virtual char do_thousands_sep() const override
            { return ',' ; } // use a comma as the group separator
    };

    const int n = 123456789 ;
    std::cout << n << '\n' ;

    // http://en.cppreference.com/w/cpp/io/basic_ios/imbue
    // http://en.cppreference.com/w/cpp/locale/locale/locale
    // note: ownership of the facet is handed over to the locale.
    // deleting the facet is its responsibility
    std::cout.imbue( std::locale( std::cout.getloc(), new numpunct_with_commas ) );
    std::cout << n << '\n' ;
}
