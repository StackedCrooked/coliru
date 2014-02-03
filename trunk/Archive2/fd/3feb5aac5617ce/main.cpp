#include <iostream>
#include <string>
#include <sstream>

struct A { std::string text ; };
struct B { std::string text ; };
struct C { std::string text ; };
struct D { std::string text ; };

std::istream& operator>> ( std::istream& is, A& a ) { return is >> a.text ; }
// the library has a templated overload for ( istream&&, T& )
// which delegates to the overload for ( istream&, T& )

B& operator>>( B& b, A& a ) { b.text += '0' ; a.text = b.text ; return b ; }

// non-template overload for (B&&, A&), which delegates to operator for (B&, A&)
B&& operator>>( B&& b, A& a ) { return std::move( b >> a ) ; } 

C& operator>>( C& c, A& a ) { c.text += "00" ; a.text = c.text ; return c ; }

// templated overload for( C&&, T& ) which delegates to operator for ( C&, T& )
template < typename T > C&& operator>>( C&& c, T& t ){ return std::move( c >> t ) ; }

D& operator>>( D& d, A& a ) { d.text += "000" ; a.text = d.text ; return d ; }
// D has no overload for ( D&&, A& )

int main()
{
    std::cout << "-----------------------\n" ;

    A x, y ;
    
    // fine, uses templated overload for ( istream&&, T& ) (with T==A)
    std::istringstream {"12 34 "} >> x >> y ; 
    std::cout << x.text << ' ' << y.text << '\n' ;

    B{"56"} >> x >> y ; // fine, uses overload for ( B&&, A& )
    std::cout << x.text << ' ' << y.text << '\n' ;
    
    C{"78"} >> x >> y ; // fine, uses templated overload for ( C&&, T& ) (with T==A)
    std::cout << x.text << ' ' << y.text << '\n' ;
    
    #ifdef USE_D
        D{"90"} >> x >> y ; // ***error: operator>> ( D&, A& ) expects l-value reference to D
        std::cout << x.text << ' ' << y.text << '\n' ;
    #endif // USE_D
    
    std::cout << "------- done ---------\n" ;
}
