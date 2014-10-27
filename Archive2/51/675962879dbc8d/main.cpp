#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct int_or_float
{
    enum type_t { INT, FLOAT };

    type_t type = INT ;

    union
    {
        int ival = 0 ;
        float fval ;
    };

    int_or_float() = default ;
    int_or_float( int v ) : type(INT), ival(v) {}
    int_or_float( double v ) : type(FLOAT), fval(v) {}

    explicit operator int() const { return std::lround( type == INT ? ival : fval ) ; }
    operator double() const { return type == INT ? ival : fval ; }
};

struct cmp_int_or_float
{
    bool operator() ( int_or_float aa, int_or_float bb ) const
    {
        const double a = aa ;
        const double b = bb ;
        return a < b ; // *** alert: assumes that these are not NaNs
    }
};

std::ostream& operator<< ( std::ostream& stm, int_or_float n )
{
    return n.type == int_or_float::INT ? ( stm << n.ival ) : ( stm << n.fval ) ;
}

std::istream& operator>> ( std::istream& stm, int_or_float& n )
{
    std::string str ;
    if( stm >> str )
    {
        try
        {
            std::size_t pos ;

            const int i = std::stoi( str, &pos ) ; // try int
            if( pos == str.size() ) // if the entire string was consumed
            {
                n = i ;
                return stm ;
            }

            const float f = std::stof( str, &pos ) ; // try float
            if( pos == str.size() ) // if the entire string was consumed
            {
                n = f ;
                return stm ;
            }
        }

        catch( const std::exception& ) {}
    }

    // input failed
    stm.clear( std::ios::failbit ) ;
    n = 0 ;
    return stm ;
}

int main()
{
    std::vector<int_or_float> numbers ;
    std::cout << std::fixed << std::showpoint << std::setprecision(2) ;

    std::istringstream stm( "1 3.5 8.4 22 22.0 3.78 2.1 2 5.6 3 8 8.0 9 21.9 input error" ) ;
    int_or_float num ;
    while( stm >> num ) numbers.push_back(num) ;

    for( auto n : numbers ) std::cout << n << ' ' ;
    std::cout << '\n' ;

    std::sort( std::begin(numbers), std::end(numbers) ) ;
    for( auto n : numbers ) std::cout << n << ' ' ;
    std::cout << '\n' ;
}
