#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

struct shifted_stdout : public std::ostream
{
    explicit shifted_stdout( std::size_t shift )
        : std::ostream( &buf ), spacer( shift, ' ' ) {}

    virtual ~shifted_stdout() { flush() ; }

    shifted_stdout& flush()
    {
        std::istringstream stm( buf.str() ) ;

        std::string line ;
        while( std::getline( stm, line ) )
            std::cout << spacer << line << '\n' ;

        buf.str("") ;
        return *this ;
    }

    private:
        std::stringbuf buf ;
        const std::string spacer ;
};

int main()
{
   shifted_stdout sout(10) ;

   sout << "hello world\n"
        << "value is: " << std::setw(8) << std::internal << -12345 << std::endl
        << "the second value is: " << std::fixed << std::setprecision(2) << 6.7
        << "\nthis line is not yet complete -- " ;

   // sout.flush() ; // NO

   sout << "line is completed now.\n" ;
}
