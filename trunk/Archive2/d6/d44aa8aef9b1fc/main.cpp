#include <iostream>
#include <iomanip>

inline bool AND( bool a, bool b ) { return a && b ; }
inline bool OR( bool a, bool b ) { return a || b ; }
inline bool XOR( bool a, bool b ) { return (a+b) == 1 ; }
inline bool NAND( bool a, bool b ) { return !(a&&b) ; }
inline bool NOR( bool a, bool b ) { return !OR(a,b) ; }
inline bool XNOR( bool a, bool b ) { return !XOR(a,b) ; }

int main()
{
    std::cout << "A B   AND NAND   OR NOR   XOR XNOR\n----------------------------------\n\n" ;
    for( bool a : { false, true } ) for( bool b : { false, true } )
    {
        std::cout << a << std::setw(2) << b
                  << std::setw(5) << AND(a,b)
                  << std::setw(4) << NAND(a,b)
                  << std::setw(6) << OR(a,b)
                  << std::setw(4) << NOR(a,b)
                  << std::setw(6) << XOR(a,b)
                  << std::setw(5) << XNOR(a,b) << "\n\n" ;
    }

    bool A = true, B = false, C = true ;
    std::cout << "\n\n(A and B) xnor((C nor A) nand(B xnor C))\n" ;
    std::cout << XNOR( AND(A,B), NAND( NOR(C,A), XNOR(B,C) ) ) << '\n' ;
}
