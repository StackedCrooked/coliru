#include <iostream>
#include <complex>
#include <string>
#include <sstream>

int main()
{
    std::istringstream file( "3+5i \n 56+72ix \n +2-3i \n 45 \n 11+22i \n 11.1+22i \n 34++7i \n -11-22i \n 26+94j \n -0-0i \n" ) ;

    std::string line ;
    while( std::getline( file, line ) )
    {
        std::istringstream stm(line) ;
        int real, imag ;
        char ch ;
        if( stm >> real >> imag >> ch && ch == 'i' && !( stm >> ch ) )
            std::cout << std::complex<double>(real,imag) << '\n' ;
        else std::cerr << "badly formed number '" << line << "'\n" ;
    }
}
