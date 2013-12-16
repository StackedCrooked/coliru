#include <iostream>
#include <string>
#include <sstream>
#include <vector>

constexpr char delimiter = '|' ;
const std::string end_marker = "end_roster|" ;

struct A
{
    explicit A( const std::string s = "", int i = 0, double d = 0 )
           :  str(s), n(i), r(d) {}

    std::string name() const { return str ; }
    int number() const { return n ; }
    double value() const { return r ; }

    private:
        std::string str ;
        int n ;
        double r ;
};

std::ostream& operator<< ( std::ostream& stm, const A& a )
{
    return stm << a.name() << delimiter << a.number() << delimiter
                << a.value() << '\n' ;
}

std::istream& operator>> ( std::istream& stm, A& a )
{
    std::string line ;
    if( std::getline(stm,line) )
    {
        std::istringstream strstm(line) ;
        char delim ;
        std::string s ;
        int n ;
        double d ;
        if( std::getline( strstm, s, delimiter ) &&
            strstm >> n >> delim && delim == delimiter &&
            strstm >> d )
        {
            a = A(s,n,d) ;
            return stm ;
        }
    }

    a = A() ; // clear the data
    stm.clear( stm.rdstate() | std::ios::failbit ) ; // put the stream in a failed state
    return stm ;
}

struct B
{
    explicit B( int i = 0, const std::string& s = "" ) : n(i), str(s) {}

    void add( const A& a ) { seq.push_back(a) ; }

    int id() const { return n ; }
    std::string name() const { return str ; }
    const std::vector<A>& objects() const { return seq ; }

    private:
        int n ;
        std::string str ;
        std::vector<A> seq ;
};

std::ostream& operator<< ( std::ostream& stm, const B& b )
{
    stm << b.id() << delimiter << b.name() << '\n' ;
    for( const A& a : b.objects() ) stm << a ;
    return stm << end_marker << '\n' ;
}

std::istream& operator>> ( std::istream& stm, B& b )
{
    std::string line ;
    if( std::getline(stm,line) )
    {
        std::istringstream istm(line) ;
        char delim ;
        int n ;
        std::string s ;
        if( istm >> n >> delim && delim == delimiter &&
            std::getline( istm, s ) )
        {
            b = B(n,s) ;
            std::string line_a ;
            while( std::getline(stm,line_a) )
            {
                std::istringstream strstm(line_a) ;
                A a ;
                if( strstm >> a ) b.add(a) ;
                else break ;
            }
            if( line_a == end_marker ) return stm ;
        }
    }
    b = B() ; // clear the data
    stm.clear( stm.rdstate() | std::ios::failbit ) ; // put the stream in a failed state
    return stm ;
}


int main()
{
     B b1( 100, "one" ) ;
     b1.add( A( "two", 200, 3.45 ) ) ;
     b1.add( A( "three", 300, 4.56 ) ) ;
     b1.add( A( "four", 400, 5.67 ) ) ;

     B b2( 500, "five" ) ;
     b2.add( A( "six", 600, 7.89 ) ) ;
     b2.add( A( "seven", 700, 8.91 ) ) ;
     b2.add( A( "eight", 800, 9.12 ) ) ;
     b2.add( A( "nine", 900, 1.23 ) ) ;

     std::string text ;
     {
         std::ostringstream stm ;
         stm << b1 << b2 ;
         text = stm.str() ;
         std::cout << text << "\n----------\n\n" ;
     }

     std::vector<B> seq ;
     std::istringstream stm(text) ;
     B b ;
     while( stm >> b ) seq.push_back(b) ;

     for( const B& b1 : seq ) std::cout << b1 ;
}
