#include <iostream>
#include <string>
#include <cstdlib> // std::exit

bool jump( const std::string& to )
{
    std::cout << "jump to loop " << to << "? " ;
    char c = 'n';
    if( std::cin >> c )
    {
        std::cout << "answer: '" << c << "'\n" ;
        return c == 'y' || c == 'Y' ;
    }

    else std::exit(0) ; // maintenance hazard: avoid except in case of catastrophic failures
                        // present here to mimic the example behavior
                        // note: destructors of local objects are *not* called
}

int main()
{
    one:
        std::cout << "loop one begin \n" ;
        std::cout << "first part of loop one code\n" ;

        if( jump("two") ) goto two ;

        std::cout << "second part of loop one code\n" ;
        std::cout << "loop one end \n" ;
        goto one ;

    two:
        std::cout << "loop two begin \n" ;
        std::cout << "first part of loop two code\n" ;

        if( jump("one") ) goto one ;

        std::cout << "second part of loop two code\n" ;
        std::cout << "loop two end \n" ;
        goto two ;
}
