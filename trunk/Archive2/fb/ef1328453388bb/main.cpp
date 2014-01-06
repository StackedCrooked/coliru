#include <iostream>
#include <sstream>

void foo( int a )
{
    std::cout << "output to stdout from function foo: " << a*a << '\n' ;
}

struct redirect_to_string // non-copyable
{
    explicit redirect_to_string( std::ostream& s ) : stm(s), oldbuf( stm.rdbuf( &buf ) ) {}
    ~redirect_to_string() { stm.rdbuf( oldbuf ) ; }

    std::string str() const { return buf.str() ; }

    redirect_to_string( const redirect_to_string& ) = delete ;
    redirect_to_string& operator= ( const redirect_to_string& ) = delete ;

    std::stringbuf buf { std::ios_base::out } ;
    std::ostream& stm ;
    std::streambuf* oldbuf ;
};

int main()
{
    // capture output of foo in a string
    std::string str ;
    {
        redirect_to_string rts(std::cout) ; // redirect output to stringbuf
        foo(23) ; // call foo; output from foo goes to the stringbuf
        str = rts.str() ; // copy contents from he stringbuf into our string
        str.pop_back() ; // remove the new-line at the end (if required)
        // note: destructor of rts will restore the original streambuf
    }

    std::cout << "string contains: '" << str << "'\n" ;
}
