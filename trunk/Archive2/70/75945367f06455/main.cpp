#include <iostream>
#include <string>

static int depth ;

static std::ostream& spacer( std::ostream& stm )
{ return stm << std::string( depth*4, ' ' ) << depth << ". " ; }

int func( int x ) {

    spacer(std::clog) << "enter function fn x == " << x << '\n' ;

    if( x<5 ) {
        spacer(std::clog)  << "x<5  return 3*x == " << 3*x << '\n' ;
		return 3*x;
	}

	else {
        spacer(std::clog) << "x>=5  return 2 * func(x-5) + 7\n" ;
        spacer(std::clog) << "x-5 == " << x-5 << " call func(" << x-5 << ")\n" ;

        ++depth ;
        int temp = func(x-5) ;
        --depth ;

        spacer(std::clog) << "func(x-5) returned " << temp << '\n' ;
        int result = 2 * temp + 7 ;
        spacer(std::clog) << "return 2 * func(x-5) + 7 == " << result << '\n' ;
        return result ;
	}
}

int main()
{
    depth = 0 ;
    func(12) ;

    std::clog << "-----------------\n" ;
    depth = 0 ;
    func(9) ;
}
