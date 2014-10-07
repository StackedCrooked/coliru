#include <iostream>
#include <string>

int main()
{
    std::string line ;
    while( std::getline( std::cin, line ) )
    {
        const auto pos = line.find( "In function" ) ;
        if( pos != std::string::npos ) std::cout << '\n'<< line.substr(pos) << '\n' ;
        else 
        {
            const auto pos_ln = line.find(':') ;
            
            if( pos_ln != std::string::npos )
            {
                const auto pos_col = line.find( ':', pos_ln+1 ) ;
                std::cout << line.substr(0,pos_ln) << " line " << line.substr( pos_ln+1, pos_col - pos_ln  - 1 ) 
                          << " col " << line.substr( pos_col+1 ) << '\n' ;
            }
            
            else std::cout << line << '\n' ;
        }
    }
}
